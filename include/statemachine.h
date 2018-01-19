/*
 * Copyright (C) 2007 Woody.Lee All rights reserved.
 */
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#define DEBUG_STATE_MACHINE 1

#include <stdio.h>
#include <memory>

#ifdef DEBUG_STATE_MACHINE
#define SM_ASSERT(x) _sm_assert(x)
inline void _sm_assert(bool c)
{
    int * pZero = 0;
    if (!c)
    {
        fprintf(stderr, "Assert Failed in StateMachine.h::assert!\n");
        *pZero = 0;
    }
}
#define PRINT_TRANSITION fprintf(stderr, "[%s]:[%d] ----%d-----> [%d]\n", name_, old_state, event_id, current_state_)
#else
#define SM_ASSERT(x)
#define PRINT_TRANSITION
#endif

template <int TRANSIT_NUM = 64>
class StateMachine
{
public:
    class TransitBase
    {
    public:
        TransitBase() {}
        virtual ~TransitBase() {}
        virtual bool isMatched(int state, int event_id) = 0;
        virtual void handleTransit(int old_state, int event_id, int& current_state_, const void* data) = 0;
        virtual void handleTransit(int old_state, int event_id, int& current_state_) = 0;
    };

    template <typename OWNER>
    class TransitWithParam : public TransitBase
    {
    public:
        typedef void (OWNER::*HandleTransitWithParam)(int old_state,
                                                      int event_id,
                                                      int& current_state,
                                                      const void* param);
        typedef void (OWNER::*HandleTransitOneParam)(const void* param);
        typedef void (OWNER::*HandleTransitWithNoParam)();
        typedef void (OWNER::*HandleTransitOnlyState)(int old_state,
                                                      int event_id,
                                                      int& current_state);

        TransitWithParam(int old_state,
                         int event_id,
                         int new_state,
                         OWNER* owner, HandleTransitWithParam handle_transit)
        : old_state_(old_state), event_id_(event_id), new_state_(new_state), owner_(owner),
          handle_transit_with_param_(handle_transit),
          handle_transit_with_no_param_(0),
          handle_transit_only_state_(0),
          handle_transit_one_param_(0)
        {
        }

        TransitWithParam(int old_state, int event_id, int new_state,
                         OWNER* owner,
                         HandleTransitWithNoParam handle_transit)
        : old_state_(old_state), event_id_(event_id), new_state_(new_state), owner_(owner),
          handle_transit_with_param_(0),
          handle_transit_with_no_param_(handle_transit),
          handle_transit_only_state_(0),
          handle_transit_one_param_(0)
        {
        }

        TransitWithParam(int old_state, int event_id, int new_state,
                         OWNER* owner,
                         HandleTransitOnlyState handle_transit)
        : old_state_(old_state), event_id_(event_id), new_state_(new_state), owner_(owner),
          handle_transit_with_param_(0),
          handle_transit_with_no_param_(0),
          handle_transit_only_state_(handle_transit),
          handle_transit_one_param_(0)
        {
        }

        TransitWithParam(int old_state, int event_id, int new_state,
                         OWNER* owner,
                         HandleTransitOneParam handle_transit)
        : old_state_(old_state), event_id_(event_id), new_state_(new_state), owner_(owner),
          handle_transit_with_param_(0),
          handle_transit_with_no_param_(0),
          handle_transit_only_state_(0),
          handle_transit_one_param_(handle_transit)
        {
        }

        virtual ~TransitWithParam()
        {
        }

        bool isMatched(int state, int event_id)
        {
            if ((state == old_state_) && (event_id == event_id_)) {
                return true;
            }
            return false;
        }

        void handleTransit(int old_state, int event_id, int& current_state, const void* data)
        {
            current_state = new_state_;
            if (handle_transit_with_param_) {
                (owner_->*handle_transit_with_param_)(old_state, event_id, current_state, data);
            }

            if (handle_transit_only_state_) {
                (owner_->*handle_transit_only_state_)(old_state, event_id, current_state);
            }

            if (handle_transit_one_param_) {
                (owner_->*handle_transit_one_param_)(data);
            }

            if (handle_transit_with_no_param_) {
                (owner_->*handle_transit_with_no_param_)();
            }
        }

        void handleTransit(int old_state, int event_id, int& current_state)
        {
            current_state = new_state_;

            if (handle_transit_with_param_) {
                (owner_->*handle_transit_with_param_)(old_state, event_id, current_state, NULL);
            }

            if (handle_transit_only_state_) {
                (owner_->*handle_transit_only_state_)(old_state, event_id, current_state);
            }

            if (handle_transit_one_param_) {
                (owner_->*handle_transit_one_param_)(NULL);
            }

            if (handle_transit_with_no_param_) {
                (owner_->*handle_transit_with_no_param_)();
            }
        }
    private:
        TransitWithParam(const TransitWithParam&);
        TransitWithParam& operator=(const TransitWithParam&);

        int old_state_;
        int event_id_;
        int new_state_;
        OWNER* owner_;
        HandleTransitWithParam handle_transit_with_param_;
        HandleTransitWithNoParam handle_transit_with_no_param_;
        HandleTransitOnlyState handle_transit_only_state_;
        HandleTransitOneParam handle_transit_one_param_;
    };

    class TransitWithNoParam : public TransitBase
    {
    public:
        TransitWithNoParam(int old_state, int event_id, int new_state)
        : old_state_(old_state), event_id_(event_id), new_state_(new_state)
        {
        }

        virtual ~TransitWithNoParam()
        {
        }

        bool isMatched(int state, int event_id)
        {
            if ((state == old_state_) && (event_id == event_id_)) {
                return true;
            }
            return false;
        }

        void handleTransit(int old_state, int event_id, int& current_state, const void* event)
        {
            current_state = new_state_;
            (void)(old_state);
            (void)(event_id);
            (void)(current_state);
            (void)(event);
        }

        void handleTransit(int old_state, int event_id, int& current_state)
        {
            (void)(old_state);
            (void)(event_id);
            current_state = new_state_;
        }
    private:
        TransitWithNoParam(const TransitWithNoParam&);
        TransitWithNoParam& operator=(const TransitWithNoParam&);

        int old_state_;
        int event_id_;
        int new_state_;
    };

    class TransitComposite
    {
    public:
        TransitComposite()
        : index_(0), transit_array()
        {}

        void addTransit(TransitBase* transit_base)
        {
            if(index_ >= TRANSIT_NUM)
            {
                fprintf(stderr, "StateMachine::TransitComposite::addTransit failed because array index overflow, system going to abort!\n");
            }
            SM_ASSERT(index_ < TRANSIT_NUM);
            transit_array[index_++].reset(transit_base);
        }

        bool handleTransit(int old_state, int event_id, int& current_state, const void* event)
        {
            bool handled = false;
            for (int i = 0; i < TRANSIT_NUM; ++i) {
                if (transit_array[i].get() != 0) {
                    TransitBase* transit = transit_array[i].get();
                    if (transit->isMatched(old_state, event_id)) {
                        transit->handleTransit(old_state, event_id, current_state, event);
                        return true;
                    }
                }
            }
            return handled;
        }

        bool handleTransit(int old_state, int event_id, int& current_state)
        {
            bool handled = false;
            for (int i = 0; i < TRANSIT_NUM; ++i) {
                if (transit_array[i].get() != 0) {
                    TransitBase* transit = transit_array[i].get();
                    if (transit->isMatched(old_state, event_id)) {
                        transit->handleTransit(old_state, event_id, current_state);
                        return true;
                    }
                }
            }
            return handled;
        }

    private:
        TransitComposite& operator=(const TransitComposite&);
        TransitComposite(const TransitComposite&);

        int index_;
        std::auto_ptr<TransitBase> transit_array[TRANSIT_NUM];
    };


    StateMachine(const char* name)
      : name_(name), current_state_(0), transit_composite_()
    {
    }

    explicit StateMachine(const char* name, int state)
      : name_(name), current_state_(state), transit_composite_()
    {}

    template<typename OWNER>
    StateMachine& addTransit(
                              int old_state,
                              int event_id,
                              int new_state,
                              OWNER* owner,
                              void (OWNER::*handleTransit)(int old_state,
                                                           int event_id,
                                                           int& current_state,
                                                           const void* param))
    {
        transit_composite_.addTransit(new TransitWithParam<OWNER>(old_state,
                                                                  event_id,
                                                                  new_state,
                                                                  owner,
                                                                  handleTransit));
        return *this;
    }

    template<typename OWNER>
    StateMachine& addTransit(
                              int old_state,
                              int event_id,
                              int new_state,
                              OWNER* owner,
                              void (OWNER::*handleTransit)())
    {
        transit_composite_.addTransit(new TransitWithParam<OWNER>(old_state,
                                                                  event_id,
                                                                  new_state,
                                                                  owner,
                                                                  handleTransit));
        return *this;
    }


    template<typename OWNER>
    StateMachine& addTransit(
                              int old_state,
                              int event_id,
                              int new_state,
                              OWNER* owner,
                              void (OWNER::*handleTransit)(int old_state,
                                                           int event_id,
                                                           int& current_state))
    {
        transit_composite_.addTransit(new TransitWithParam<OWNER>(old_state,
                                                                  event_id,
                                                                  new_state,
                                                                  owner,
                                                                  handleTransit));
        return *this;
    }

    template<typename OWNER>
    StateMachine& addTransit(
                              int old_state,
                              int event_id,
                              int new_state,
                              OWNER* owner,
                              void (OWNER::*handleTransit)(const void* event))
    {
        transit_composite_.addTransit(new TransitWithParam<OWNER>(old_state,
                                                                  event_id,
                                                                  new_state,
                                                                  owner,
                                                                  handleTransit));
        return *this;
    }

    StateMachine& addTransit(
                              int old_state,
                              int event_id,
                              int new_state)
    {
        transit_composite_.addTransit(new TransitWithNoParam(old_state, event_id, new_state));
        return *this;
    }

    void startState(int state)
    {
        current_state_ = state;
    }

    int getState() const
    {
        return current_state_;
    }

    void updateState(int event_id, const void* event)
    {
        int old_state = current_state_;
        if (transit_composite_.handleTransit(old_state, event_id, current_state_, event))
        {
            PRINT_TRANSITION;
        }
    }

    void updateState(int event_id)
    {
        int old_state = current_state_;
        if (transit_composite_.handleTransit(old_state, event_id, current_state_))
        {
            PRINT_TRANSITION;
        }
    }


private:
    const char* name_;
    int current_state_;
    TransitComposite transit_composite_;
};

#endif /* STATEMACHINE_H */

