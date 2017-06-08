#ifndef EVENT_NOTIFIER_H
#define EVENT_NOTIFIER_H

#include <vector>
#include <algorithm>

namespace pzr
{   
    template <typename EventAction>
    class EventListner
    {
    public:
        ~EventListner() {};
        virtual void onNotified(EventAction event) = 0;
    };

    template<typename EventAction>
    class EventNotifier
    {
    public:
        ~EventNotifier() {};
        void registerListener(EventListner<EventAction>* listner);
        void removeListener(EventListner<EventAction>* listner);
        void notify(EventAction currentEvent);
    
    protected:
        std::vector<EventListner<EventAction>*> _listners;
    };

    
    template<typename EventAction>
    void EventNotifier<EventAction>::registerListener(EventListner<EventAction>* listner)
    {
        _listners.push_back(listner);
    }

    template<typename EventAction>
    void EventNotifier<EventAction>::removeListener(EventListner<EventAction>* listner)
    {
        _listners.erase(std::remove(_listners.begin(), _listners.end(), listner), _listners.end());
    }

    template<typename EventAction>
    void EventNotifier<EventAction>::notify(EventAction currentEvent)
    {
        for (EventListner<EventAction>* listner : _listners)
        {
            listner->onNotified(currentEvent);
        }
    }
}

#endif


