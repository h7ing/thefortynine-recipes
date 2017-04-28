//
//  fnbehaviourtree.cpp
//
//  Created by h7ing on 15/Feb/2017.
//  Copyright © 2017 h7ing. All rights reserved.
//

#include "fnbehaviourtree.hpp"

namespace fn {
    
    // MARK:--------------------------------------------------------------------
    
    std::unique_ptr<BehaviourTree> BehaviourTree::create() {
        return std::unique_ptr<BehaviourTree>(new BehaviourTree);
    }
    
    BehaviourTree::BehaviourTree() {
        
    }
    
    BehaviourTree::BehaviourTree(BehaviourNodeUPtr the_root_node) : root_node(std::move(the_root_node)) {
    }
    
    void BehaviourTree::update() {
        root_node->visit();
    }
    
    void BehaviourTree::setRootNode(BehaviourNodeUPtr root) {
        root_node = std::move(root);
    }
    
    
    // MARK:--------------------------------------------------------------------
    
    BehaviourNode::BehaviourNode() {
    }
    
    BehaviourNode::~BehaviourNode() {
    }
    
    void BehaviourNode::visit() {
        status = BHStatus::FAILED;
    }
    
    void BehaviourNode::reset() {
        if (BHStatus::READY == status)
            return;
        
        status = BHStatus::READY;
        for (auto&& child : children) {
            child->reset();
        }
    }
    
    void BehaviourNode::addChild(BehaviourNodeUPtr child) {
        children.push_back(std::move(child));
    }
    
    // MARK:--------------------------------------------------------------------
    
    std::unique_ptr<SequenceNode> SequenceNode::create() {
        return std::unique_ptr<SequenceNode>(new SequenceNode);
    }
    
    SequenceNode::SequenceNode() {
    }
    
    SequenceNode::~SequenceNode() {
    }
    
    void SequenceNode::visit() {
        if (BHStatus::RUNNING != status) {
            _current = 0;
        }
        
        for (; _current < children.size(); _current++) {
            auto &&child = children[_current];
            child->visit();
            auto s = child->status;
            if (BHStatus::FAILED == s || BHStatus::RUNNING == s) {
                status = s;
                return;
            }
        }
        
        status = BHStatus::SUCCESS;
    }
    
    // MARK:--------------------------------------------------------------------
    
//    SelectorNode::SelectorNode() {
//        
//    }
//    
//    SelectorNode::~SelectorNode()
//    {
//    }
//    
////    SelectorNode::SelectorNode(const BehaviourNodePtr &child) :
////    BehaviourNode(child)
////    {
////    }
//    
////    SelectorNode::SelectorNode(const ChildrenSPtr& children) :
////    BehaviourNode(children)
////    {
////    }
//    
//    void SelectorNode::visit()
//    {
//        if (BHStatus::RUNNING != status) {
//            _current = 0;
//        }
//        for (; _current < children.size(); _current++) {
//            auto &&child = children[_current];
//            child->visit();
//            auto s = child->status;
//            if (BHStatus::SUCCESS == s || BHStatus::RUNNING == s) {
//                status = s;
//                return;
//            }
//        }
//        
//        status = BHStatus::FAILED;
//    }
//    
//    //-----------------------------------------------------------------------------
//    
//    DecoratorNode::DecoratorNode() {
//        
//    }
//    
//    DecoratorNode::~DecoratorNode()
//    {
//    }
//    
////    DecoratorNode::DecoratorNode(const BehaviourNodePtr &child) : BehaviourNode(child)
////    {
////        
////    }
//    
//    //-----------------------------------------------------------------------------
//    
//    std::unique_ptr<ActionNode> ActionNode::create(const Action & ac)
//    {
//        auto pret = std::unique_ptr<ActionNode>(new ActionNode(ac));
//        return pret;
//    }
//    
//    ActionNode::~ActionNode()
//    {
//    }
//    
//    ActionNode::ActionNode(const Action &ac) : action(ac)
//    {
//        
//    }
//    
//    void ActionNode::visit()
//    {
//        action();
//        status = BHStatus::SUCCESS;
//    }
    
    // MARK:--------------------------------------------------------------------
    
    std::unique_ptr<ConditionNode> ConditionNode::create(const Condition &cond) {
        return std::unique_ptr<ConditionNode>(new ConditionNode(cond));
    }
    
    ConditionNode::~ConditionNode() {
    }
    
    ConditionNode::ConditionNode(const Condition &cond) : condition(cond) {
    }
    
    void ConditionNode::visit() {
        if (condition())
            status = BHStatus::SUCCESS;
        else
            status = BHStatus::FAILED;
    }
    
//    //-----------------------------------------------------------------------------
//    
//    ParallelNode::ParallelNode() {
//        
//    }
//    
//    ParallelNode::~ParallelNode()
//    {
//    }
//    
////    ParallelNode::ParallelNode(const BehaviourNodePtr & child, Policy poSucc, Policy poFail) :
////    BehaviourNode(child), successPolicy(poSucc), failedPolicy(poFail)
////    {
////    }
//    
////    ParallelNode::ParallelNode(const ChildrenSPtr& children, Policy poSucc, Policy poFail) :
////    BehaviourNode(children), successPolicy(poSucc), failedPolicy(poFail)
////    {
////    }
//    
//    void ParallelNode::visit()
//    {
//        int succCnt = 0;
//        int failCnt = 0;
//        for (auto &&pChild : children) {
//            pChild->visit();
//            auto s = pChild->status;
//            if (BHStatus::SUCCESS == s) {
//                succCnt++;
//                if (Policy::REQUIRE_ONE == successPolicy) {
//                    status = BHStatus::SUCCESS;
//                    return;
//                }
//            }
//            else if (BHStatus::FAILED == s) {
//                failCnt++;
//                if (Policy::REQUIRE_ONE == failedPolicy) {
//                    status = BHStatus::FAILED;
//                    return;
//                }
//            }
//            
//            if (Policy::REQUIRE_ALL == successPolicy && succCnt == children.size()) {
//                status = BHStatus::SUCCESS;
//                return;
//            }
//            else if (Policy::REQUIRE_ALL == failedPolicy && failCnt == children.size()) {
//                status = BHStatus::FAILED;
//                return;
//            }
//            
//            status = BHStatus::RUNNING;
//        }
//    }
    
    // MARK:--------------------------------------------------------------------
    
    std::unique_ptr<IfNode> IfNode::create(const Condition &if_cond, BehaviourNodeUPtr then_node) {
        return std::unique_ptr<IfNode>(new IfNode(if_cond, std::move(then_node)));
    }
    
    IfNode::~IfNode() {
    }
    
    IfNode::IfNode(const Condition &if_cond, BehaviourNodeUPtr then_node) {
        addChild(ConditionNode::create(if_cond));
        addChild(std::move(then_node));
    }
    
//    //-----------------------------------------------------------------------------
//    
//    WhileNode::~WhileNode()
//    {
//    }
//    
//    WhileNode::WhileNode(const std::shared_ptr<ConditionNode> &cond, const BehaviourNodeUPtr node)
//    {
//        children.push_back(std::move(node));
//    }
//    
    // MARK:--------------------------------------------------------------------
}
