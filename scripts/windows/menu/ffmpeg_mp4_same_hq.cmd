"d:\Program Files\FFMpeg_aac\ffmpeg.exe" -i %1 -c:v libx264 -crf 19 -c:a libfdk_aac -b:a 320k %~n1_same_hq.mp4