set /p from="from (00:00:00): "
set /p time="time (30): "
"d:\Program Files\FFMpeg_aac\ffmpeg.exe" -i %1 -c:v libx264 -preset slow -crf 15 -c:a flac -c:a libfdk_aac -b:a 320k -ss %from% -t %time% %~n1_cut.mp4
