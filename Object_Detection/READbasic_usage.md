
**Shell script**
Using your shell script(.sh), you can launch the same three lines each time to test any changes made to your python script(.py)

'''
cd tflite1/
source tflite1-env/bin/activate
python3 TFLite_mayra.py --modeldir=Sample_TFLite_model
'''

again 
'''
cd tflite/
'''
Changes from home directory to tflite1/ folder since this is where we have our subfolders

'''
source tflite1-env/bin/activate
'''
Starts our TensorFlow Lite virtual environment called "tflite1-env"
for more info on virtual environments see:
https://docs.python.org/3/tutorial/venv.html

'''
python3 TFLite_mayra.py --modeldir=Sample_TFLite_model
'''
run python3 script called "TFLite_mayra.py" with arguments --modeldir=Sample_TFLite_model
where --modeldir=Sample_TFLite_model specifies the subdirectory of our model files 


