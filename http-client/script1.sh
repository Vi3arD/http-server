#!/bin/bash
for i in `seq 1 100`;
do
        ./httpclient 127.0.0.1 /index.htm
done