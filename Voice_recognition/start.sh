cd 
source $HOME/tmp/deepspeech-venv/bin/activate
python3 DeepSpeech-examples/mic_vad_streaming/mic_vad_streaming.py --device 1 -m deepspeech-0.7.4-models.tflite -s deepspeech-0.7.4-models.scorer
