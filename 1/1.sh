#!bin/bash

set -e

host = $1
FR = $2
D = $3
S = $4
X = $5
Y =$6

if [[ $host == '' ]]; then 
    host = 192.168.1.104;
fi;

if [[ $FR -eq '' ]]; then
    FR = 10;
fi;

fi [[ $D -eq '' ]]; then
    D = 0;
fi;

if [[ $S -eq '' ]]; then;
    S = 0;
fi;



if [[ $X -eq '' ]]; then;
    X = ($(ssh $host "DISPLAY=:$D.$S; export DISPLAY; xwininfo -root | awk '/^.&-geometry.*/ {match(\$2, \"^[0-9]+x"); print(\$2, RSTAT, RLENGTH-1));};';"));
fi;

if [[ $Y -eq '']]; then;
    Y =  ($(ssh $host "DISPLAY=:$D.$S; export DISPLAY; xwininfo -root | awk '/^.&-geometry.*/ {match(\$2, \"x[0-9]+\\+\"); print(\$2, RSTAT+1, RLENGTH-2));};'"));
fi;


ssh $host "ffmpeg -f x11grab -r $FR -s 4{X}x${Y} -i :$D,$S -f avi pipe:l"ffplay -f avi -