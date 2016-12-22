#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED
/*
 *  This is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *  The software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  You should have received a copy of the GNU General Public License
 *  along with the software. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright 2017, Willem L, Kuylen E, Stijven S & Broeckhove J
 */

/**
 * @file
 * Header file for the Person class.
 */

#include "core/Health.h"

#include <cstddef>
#include <memory>

namespace stride {

class Calendar;
enum class ClusterType;

/**
 * Store and handle person data.
 */
class Person
{
public:
	/// Constructor: set the person data.
	Person(unsigned int id, double age, unsigned int household_id, unsigned int home_district_id,
			unsigned int day_cluster_id, unsigned int day_district_id, unsigned int start_infectiousness,
			unsigned int start_symptomatic, unsigned int time_infectious, unsigned int time_symptomatic)
		: m_id(id), m_age(age), m_gender('M'),
		  m_household(household_id), m_home_district(home_district_id),
		  m_day_cluster(day_cluster_id), m_day_district(day_district_id),
		  m_in_household(true), m_in_home_district(true),
		  m_in_day_cluster(true), m_in_day_district(true),
		  m_health(start_infectiousness, start_symptomatic, time_infectious, time_symptomatic),
		  m_is_participant(false) {}

	/// Is this person not equal to the given person?
	bool operator!=(const Person& p) const { return p.m_id != m_id; }

	/// Get the age.
	double GetAge() const { return m_age; }

	/// Get cluster ID of cluster_type
	unsigned int GetClusterId(ClusterType cluster_type) const;

        ///
	char GetGender() const { return m_gender; }

        ///
	size_t GetHouseholdSize() const { return m_household_size; }

	///
	Health& GetHealth()  { return m_health; }

	///
	const Health& GetHealth() const { return m_health; }

	/// Get the id.
        unsigned int GetId() const { return m_id; }

        /// Check if a person is present today in a given cluster
        bool IsInCluster(ClusterType c) const;

	/// Does this person participates in the social contact study?
	bool IsParticipatingInSurvey() const { return m_is_participant; }

	/// Participate in social contact study and log person details
	void ParticipateInSurvey() { m_is_participant = true; }

	///
	void SetHouseholdSize(size_t hh_size) { m_household_size = hh_size; }

	/// Update the health status and presence in clusters.
	void Update(std::shared_ptr<const Calendar> calendar);

private:
	unsigned int    m_id;		       		 ///< The id.
	double          m_age;		       		 ///< The age.
	char            m_gender;                        ///< The gender.

	unsigned int    m_household;	   		 ///< The household id.
	std::size_t     m_household_size;		 ///< The number of persons in the household.
	unsigned int    m_home_district;   		 ///< The home district id
	unsigned int    m_day_cluster;	   		 ///< The day cluster id
	unsigned int    m_day_district;	   		 ///< The day district id

	bool            m_in_household;			 ///< Is person present in household today?
	bool            m_in_home_district;		 ///< Is person present in home_district today?
	bool            m_in_day_cluster;		 ///< Is person present in day_cluster today?
	bool            m_in_day_district;		 ///< Is person present in day_district today?

	Health          m_health;                        ///< Health info for this person.

	bool            m_is_participant;		 ///< Is participating in the social contact study
};

} // end_of_namespace

#endif // end of include guard
