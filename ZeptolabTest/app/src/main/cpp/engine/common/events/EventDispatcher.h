//
// Created by Josep on 27/08/2018.
//

#ifndef ZEPTOLABTEST_EVENTDISPATCHER_H
#define ZEPTOLABTEST_EVENTDISPATCHER_H

#include "EventPool.h"

#include <vector>
#include <map>
#include <functional>

namespace events
{
    class EventDispatcher
    {
    public:
        using CallBack = std::function< void ( const Event& ) >;

        /**
         * Static class. Delete all special functions.
         */
        EventDispatcher() = delete;
        ~EventDispatcher() = delete;
        EventDispatcher(const EventDispatcher& aOther) = delete;
        EventDispatcher(EventDispatcher&& aOther) = delete;
        EventDispatcher& operator=(const EventDispatcher& aOther) = delete;
        EventDispatcher& operator=(EventDispatcher&& aOther) = delete;

        /**
         * Remove all listeners from the list, reseting the event dispatcher to zero listeners.
         */
        static void ReleaseAllListeners();

        /**
         * Adds a new listener to the list, by specifying a Event to subscribe, and a callback to
         * call when it receives the event.
         * @param aEventDescriptor Event descriptor to subscribe.
         * @param aCallBack Callback to call.
         */
        static void StartListening( const Event::DescriptorType& aEventDescriptor,
                                    CallBack aCallBack);

        /**
         * Sends a new event.
         * @param aEvent Event to be sent.
         */
        static void SendEvent( const Event& aEvent);

    private:
        typedef  std::map<Event::DescriptorType , std::vector<CallBack> > ListenersMap;
        // Map of listeners.
        static ListenersMap mListeners;
    };


}

#endif //ZEPTOLABTEST_EVENTDISPATCHER_H
