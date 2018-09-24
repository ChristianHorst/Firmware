
/***************************************************************************
 *
 *   Copyright (c) 2018 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
/**
 * @file ams.h
 * Helper class for AMS (Auto Maneuver System)
 *
 * @author Mathieu Bresciani <brescianimathieu@gmail.com>
 */

#pragma once

#include <px4_module_params.h>

#include "navigator_mode.h"
#include "mission_block.h"

class Navigator;

class AMS : public MissionBlock, public ModuleParams
{
public:
	enum class AMSType {
		AMS_LOITER = 0,
		AMS_LAND,
		AMS_RALLY,
	};

	AMS(Navigator *navigator);

	~AMS() = default;

	void on_inactive() override;
	void on_activation() override;
	void on_active() override;

	AMSType ams_type() const {return static_cast<AMSType>(_param_ams_type.get())};

private:
	/**
	 * Set the AMS item
	 */
	void		set_ams_item();

	/**
	 * Move to next AMS item
	 */
	void		advance_ams();

	int ams_alt() const {return _param_ams_descend_alt};
	int ams_vel() const {return _param_ams_descend_vel};

	enum AMSState {
		AMS_STATE_NONE = 0,
		AMS_STATE_TRANSITION_TO_MC,
		AMS_STATE_DESCEND,
		AMS_STATE_LOITER,
		AMS_STATE_LAND,
		AMS_STATE_LANDED,
	} _ams_state{AMS_STATE_NONE};

	bool _ams_alt_min{false};

	DEFINE_PARAMETERS(
		(ParamFloat<px4::params::AMS_DESCEND_ALT>) _param_ams_descend_alt,
		(ParamFloat<px4::params::AMS_DESCEND_VEL>) _param_ams_descend_vel,
		(ParamInt<px4::params::AMS_TYPE>) _param_ams_type
	)
};
