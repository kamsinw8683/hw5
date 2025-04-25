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
bool scheduleHelper(
    const AvailabilityMatrix &avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule &sched,
    int currentDay,
    int position,
    vector<int> &shiftList)
{

    if (currentDay == sched.size())
    {
        return true;
    }
    for (size_t worker = 0; worker < avail[currentDay].size(); ++worker)
    {
        bool isAvailable = (avail[currentDay][worker] == 1);
        bool canWorkMore = (shiftList[worker] < maxShifts);
        bool notScheduledToday = (find(sched[currentDay].begin(), sched[currentDay].end(), worker) == sched[currentDay].end());

        if (isAvailable && canWorkMore && notScheduledToday)
        {
            sched[currentDay][position] = worker;
            shiftList[worker]++;
            bool success;

            if (position == dailyNeed - 1)
            {
                success = scheduleHelper(avail, dailyNeed, maxShifts, sched, currentDay + 1, 0, shiftList);
            }
            else
            {
                success = scheduleHelper(avail, dailyNeed, maxShifts, sched, currentDay, position + 1, shiftList);
            }
            if (success)
            {
                return true;
            }
            // Backtrack if not successful
            shiftList[worker]--;
            sched[currentDay][position] = INVALID_ID;
        }
    }

    return false;
}

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

    vector<int> shiftList(avail[0].size(), 0);
    sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0, shiftList);
}