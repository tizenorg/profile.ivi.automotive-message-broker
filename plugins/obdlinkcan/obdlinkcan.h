/*
Copyright (C) 2012 Intel Corporation

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef ObdLinkCANPLUGIN_H
#define ObdLinkCANPLUGIN_H

#include <abstractsource.h>
#include <string>

using namespace std;

class ObdLinkCAN: public AbstractSource
{

public:
	ObdLinkCAN(AbstractRoutingEngine* re, map<string, string> config);
	
	const string uuid();
	void getPropertyAsync(AsyncPropertyReply *reply);
	void getRangePropertyAsync(AsyncRangePropertyReply *reply);
	AsyncPropertyReply * setProperty(AsyncSetPropertyRequest request);
	void subscribeToPropertyChanges(VehicleProperty::Property property);
	void unsubscribeToPropertyChanges(VehicleProperty::Property property);
	PropertyList supported();

	int supportedOperations();
	
	void supportedChanged(PropertyList) {}
	
	void randomizeProperties();

	PropertyInfo getPropertyInfo(VehicleProperty::Property property)
	{
		if(propertyInfoMap.find(property) != propertyInfoMap.end())
			return propertyInfoMap[property];

		return PropertyInfo::invalid();
	}
	
private:

	void addPropertySupport(VehicleProperty::Property property, Zone::Type zone);

	std::map<VehicleProperty::Property, PropertyInfo> propertyInfoMap;
	std::map<Zone::Type, Airbag::Status> airbagStatus;
	std::map<Zone::Type, bool> acStatus;
	PropertyList mRequests;
	PropertyList mSupported;
	uint16_t velocity;
	uint16_t engineSpeed;
};

#endif // ObdLinkCANPLUGIN_H
