#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix &avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule &sched)
{
    if (avail.size() == 0U)
    {
        return false;
    }
    sched.clear();
    // Add your code below
    sched.resize(avail.size());
    for (size_t i = 0; i < avail.size(); i++) {
        sched[i].resize(dailyNeed, INVALID_ID);
    }
    
    // Initialize shift count for each worker
    vector<size_t> shifts(avail[0].size(), 0);
    
    return findSchedule(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);
}
bool canScheduleWorker(const AvailabilityMatrix &avail, const DailySchedule &sched,
                       const vector<size_t> &shifts, size_t day, Worker_T worker,
                       size_t maxShifts)
{
    // Check if worker is available
    if (!avail[day][worker])
    {
        return false;
    }

    if (shifts[worker] >= maxShifts)
    {
        return false;
    }

    // Check if worker is already scheduled for this day
    for (size_t i = 0; i < sched[day].size(); i++)
    {
        if (sched[day][i] == worker)
        {
            return false;
        }
    }

    return true;
}

bool findSchedule(const AvailabilityMatrix &avail, const size_t dailyNeed,
                  const size_t maxShifts, DailySchedule &sched,
                  vector<size_t> &shifts, size_t day, size_t pos)
{
    // Base case: if we've scheduled all days
    if (day == avail.size())
    {
        return true;
    }

    // Base case: if we've filled all positions for this day
    if (pos == dailyNeed)
    {
        return findSchedule(avail, dailyNeed, maxShifts, sched, shifts, day + 1, 0);
    }

    for (Worker_T worker = 0; worker < avail[0].size(); worker++)
    {
        if (canScheduleWorker(avail, sched, shifts, day, worker, maxShifts))
        {
            sched[day][pos] = worker;
            shifts[worker]++;

            if (findSchedule(avail, dailyNeed, maxShifts, sched, shifts, day, pos + 1))
            {
                return true;
            }

            // Backtrack
            shifts[worker]--;
        }
    }

    return false;
}
