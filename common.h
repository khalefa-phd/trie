#pragma once
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#ifdef __GNUC__
#include <bits/stdc++.h>
#endif

extern const char* gitversion;
#ifdef __GNUC__
#define __FILENAME__                                                           \
   (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1    \
                                     : __FILE__)
#else
#define __FILENAME__ "TEST"
#endif

#ifdef __STAT__
#define REP 1.0
#else
#ifdef __GNUC__
#define REP 5.0
#else
#define REP 1.0
#endif
#endif

using namespace std;

const int ALPHABET_SIZE = 26;
const double D_TOP_K_MAX_VALUE = 1000, D_TAU_WEIGHT = 1.0,
             D_LENGTH_WEIGHT = 0.0, D_FREQUENCY_WEIGHT = 0.0;

#ifdef __GNUC__
static void escape(void* p) { asm volatile("" : : "g"(p) : "memory"); }
static void clobber(void* p) { asm volatile("" : : : "memory"); }
#else
static void escape(void* p) {}
static void clobber(void* p) {}
#endif
