#pragma once

#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include <string>
#include <random_stuff.h>

void convert_test_ranges_ins();
bool test_run_small(void (*test_funct)(range*, range, int*));
void display_test_range();

#endif
