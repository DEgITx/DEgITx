ffmpeg -i %1 -ar 44100 -q:a 2 -sample_fmt s16p %~n1_vbr2.mp3