//
//  fnbehaviourtree.hpp
//
//  Created by h7ing on 15/Feb/2017.
//  Copyright © 2017 h7ing. All rights reserved.
//

#ifndef BehaviourTree_hpp
#define BehaviourTree_hpp

#include <memory>
#include <vector>
#include <functional>

namespace fn {
    
    // MARK:--------------------------------------------------------------------
    
    class Entity;
    class BehaviourNode;
    
    enum class BHStatus {
        READY,
        SUCCESS,
        FAILED,
        RUNNING
    };
    
    typedef std::unique_ptr<BehaviourNode> BehaviourNodeUPtr;
    typedef std::function<bool()> Condition;
    
    
    // MARK:--------------------------------------------------------------------
    
    class BehaviourTree {
    public:
        static std::unique_ptr<BehaviourTree> create();
        BehaviourTree();
        explicit BehaviourTree(BehaviourNodeUPtr the_root_node);
        
        void update();
        
        void setEntity(Entity *the_entity) {
            entity = the_entity;
        }
        
        void setRootNode(BehaviourNodeUPtr root);
        
    protected:
        Entity *entity = nullptr;
        BehaviourNodeUPtr root_node = nullptr;
    };
    
    typedef std::shared_ptr<BehaviourTree> BehaviourTreePtr;
    
    
    // MARK:--------------------------------------------------------------------
    
    class BehaviourNode {
    public:
        Entity *entity = nullptr;
        BHStatus status = BHStatus::READY;
    public:
        BehaviourNode();
        virtual ~BehaviourNode();
        
        virtual void visit();
        virtual void reset();
        
        void addChild(BehaviourNodeUPtr child);
        
    protected:
        std::vector<BehaviourNodeUPtr> children;
    };
    
    
    // MARK:--------------------------------------------------------------------
    
    
    class SequenceNode : public BehaviourNode {
    public:
        static std::unique_ptr<SequenceNode> create();
        SequenceNode();
        virtual ~SequenceNode();
        virtual void visit() override;
        
    private:
        size_t _current = 0;
    };
    
    
    // MARK:--------------------------------------------------------------------
    
    
//    class SelectorNode : public BehaviourNode {
//    public:
//        SelectorNode();
//        virtual ~SelectorNode();
////        explicit SelectorNode(const BehaviourNodePtr &child);
////        explicit SelectorNode(const ChildrenSPtr &children);
//        virtual void visit() override;
//        
//    private:
//        size_t _current = 0;
//    };
//    
//    
//    //-----------------------------------------------------------------------------
//    
//    
//    class DecoratorNode : public BehaviourNode {
//    public:
//        DecoratorNode();
//        virtual ~DecoratorNode();
////        explicit DecoratorNode(const BehaviourNodePtr &child);
//    };
//    
//    
//    //-----------------------------------------------------------------------------
//    
//    
//    class ActionNode : public BehaviourNode {
//    public:
//        typedef std::function<void()> Action;
//    public:
//        static std::unique_ptr<ActionNode> create(const Action &ac);
//        virtual ~ActionNode();
//        explicit ActionNode(const Action &ac);
//        virtual void visit() override;
//        
//        Action action;
//    };
    
    
    // MARK:--------------------------------------------------------------------
    
    
    class ConditionNode : public BehaviourNode {
    public:
        Condition condition;
    public:
        static std::unique_ptr<ConditionNode> create(const Condition &cond);
        virtual ~ConditionNode();
        ConditionNode() = delete;
        explicit ConditionNode(const Condition &cond);
        virtual void visit() override;
    };
    
    
//    //-----------------------------------------------------------------------------
//    
//    
//    class ParallelNode : public BehaviourNode {
//    public:
//        enum class Policy {
//            REQUIRE_ONE,
//            REQUIRE_ALL
//        };
//    public:
//        ParallelNode();
//        virtual ~ParallelNode();
////        ParallelNode(const BehaviourNodePtr &child, Policy poSucc, Policy poFail);
////        ParallelNode(const ChildrenSPtr &children, Policy poSucc, Policy poFail);
//        virtual void visit() override;
//        
//        Policy successPolicy = Policy::REQUIRE_ONE;
//        Policy failedPolicy = Policy::REQUIRE_ONE;
//    };
    
    
    // MARK:--------------------------------------------------------------------
    
    class IfNode : public SequenceNode {
    public:
        static std::unique_ptr<IfNode> create(const Condition &if_cond, BehaviourNodeUPtr then_node);
        virtual ~IfNode();
        IfNode(const Condition &if_cond, BehaviourNodeUPtr then_node);
    };
    
    
//    //-----------------------------------------------------------------------------
//    
//    class WhileNode : public ParallelNode {
//    public:
//        virtual ~WhileNode();
//        WhileNode(const std::shared_ptr<ConditionNode> &cond, BehaviourNodeUPtr node);
//    };
    
    // MARK:--------------------------------------------------------------------
}

#endif /* BehaviourTree_hpp */
