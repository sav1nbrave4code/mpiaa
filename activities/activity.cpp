#include "activity.h"

// Default less operator - sorts by start time first.
auto Activity::operator<(const Activity &a) const -> bool
{
	return (start < a.start || (start == a.start && finish < a.finish));
}

// Default equal operator.
auto Activity::operator==(const Activity &a) const -> bool
{
	return (start == a.start && finish == a.finish);
}

Activity::Activity(const int start, const int finish) :
    start{start},
    finish{finish}
{}
