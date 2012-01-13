#!/bin/bash

ls *.cpp *.hpp | while read file; do 
  ( echo "/*!
* \file ${file}
* \brief 
* \author Thomas Macdonald
* \date $(date)
*/"; cat ${file} ) > ${file}.new && mv ${file}.new ${file}
done
