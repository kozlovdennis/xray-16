#pragma once
#include "StdAfx.h"
#include "xrCore/Animation/Envelope.hpp"
#include "xrCore/Animation/Motion.hpp"

EChannelType GetChannelType(LWChannelID chan);
// Use the Animation Envelopes global to get the keys of an LWEnvelope and create our own version.
CEnvelope* CreateEnvelope(LWChannelID chan, LWChannelID* chan_parent = nullptr);
