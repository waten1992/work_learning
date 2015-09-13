/*
   * File name : rss_quote_query.h
   *
   * Author	: He Wen Guan
   *
   * Description : 
   *            quote query library .
   *
   * Copyright (c) 2007-2015 MY Capital Inc.
   *
   */

#ifndef RSS_QUOTE_QUERY_H
#define RSS_QUOTE_QUERY_H

#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct rss_quote_query;
struct rss_quote_query_at;

struct rss_quote_query *
rss_quote_query_load(const char* rss_quote_query_path);

int 
rss_quote_query_get_cnt(struct rss_quote_query *p ,uint64_t *get_cnt);

void *
rss_quote_query_at(struct rss_quote_query_at *p );

int 
rss_quote_query_unload(struct rss_quote_query *p);

#endif

