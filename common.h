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

#if !defined(__STAT__) && !defined(__EXPR__)
#define __TEST__
#define REP 1
#endif

#ifdef __STAT__
#define REP 1
#undef __EXPR__
#endif

#ifdef __EXPR__
#undef __STAT__
#define REP 5
#endif

using namespace std;

#ifdef __TEST__
#ifndef __GNUC__
#define __2DIM__
#endif
#endif

const int ALPHABET_SIZE = 26;
#ifdef __1DIM__
const string EXPR = "1DIM";
const int D_TOP_K_MAX_VALUE = 1000, D_TAU_WEIGHT = 1, D_LENGTH_WEIGHT = 0,
          D_FREQUENCY_WEIGHT = 0;
#else
#ifdef __2DIM__
const string EXPR = "2DIM";
const double D_TOP_K_MAX_VALUE = 1000, D_TAU_WEIGHT = 0.5,
             D_LENGTH_WEIGHT = 0.25, D_FREQUENCY_WEIGHT = 0.25;

#else
#error Define either 1dim or 2 dim
#endif
#endif

#ifdef __GNUC__
static void escape(void* p) { asm volatile("" : : "g"(p) : "memory"); }
static void clobber(void* p) { asm volatile("" : : : "memory"); }
#else
static void escape(void* p) {}
static void clobber(void* p) {}
#endif
