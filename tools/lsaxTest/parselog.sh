#!/bin/bash

#cat jfe.log  | awk -F '#?#  :' '{print NF}'
#cat jfe.log  | awk -F "#?#  :" '{for (i=1;i<=NF;i++) printf("%s\n", $i); }'

./lsaxtest -p jfe.log 

