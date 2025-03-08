#ifndef STATS_H
#define STATS_H

typedef struct {
	int hits;
	int misses;
	int shots;
	float hit_miss_ratio;
	bool has_won;
} Stats;

#endif  // STATS_H