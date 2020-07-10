#!/bin/env bash
printf "H"&&uuid|tr -d '-'|tr -s '[:lower:]' '[:upper:]'
