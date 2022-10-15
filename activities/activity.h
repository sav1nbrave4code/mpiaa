#pragma once

class Activity
{
public:
    Activity() = default;        
    Activity(int start, int finish);

    auto operator<(const Activity &a) const -> bool;
    auto operator==(const Activity &a) const -> bool;

public:
    int start  {0};
    int finish {0};
};
