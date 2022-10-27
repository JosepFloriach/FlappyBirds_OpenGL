//
// Created by Josep on 27/08/2018.
//

#include "EventDispatcher.h"
namespace events
{
    EventDispatcher::ListenersMap EventDispatcher::mListeners = {};

    void EventDispatcher::StartListening( const Event::DescriptorType& aEventDescriptor,
                                          CallBack aCallBack)
    {
        mListeners[aEventDescriptor].push_back(aCallBack);
    }

    void EventDispatcher::ReleaseAllListeners()
    {
        mListeners.clear();
    }

    void EventDispatcher::SendEvent( const Event& aEvent)
    {
        auto type = aEvent.Type();
        if (mListeners.find(type) == mListeners.end())
            return;

        auto&& CallBacks = mListeners.at(type);
        for(auto&& CallBack: CallBacks)
        {
            CallBack(aEvent);
        }
    }
}