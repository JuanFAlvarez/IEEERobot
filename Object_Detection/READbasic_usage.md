
**Shell script**

These are located in /home/pi

Using your shell script(.sh), you can launch the same three lines each time to test any changes made to your python script(.py)
```
cd tflite1/
source tflite1-env/bin/activate
python3 TFLite_mayra.py --modeldir=Sample_TFLite_model
```



again 
```
cd tflite/
```

Changes from home directory to tflite1/ folder since this is where we have our subfolders



```
source tflite1-env/bin/activate
```

Starts our TensorFlow Lite virtual environment called "tflite1-env"
for more info on virtual environments see:
https://docs.python.org/3/tutorial/venv.html



```
python3 TFLite_mayra.py --modeldir=Sample_TFLite_model
```

runs python3 script called "TFLite_mayra.py" with arguments --modeldir=Sample_TFLite_model
where --modeldir=Sample_TFLite_model specifies the subdirectory of our model files 






**Considerations for python code**

-Multiple distinct objects detected

	ex: detecting a person and a backpack at the same time

-Have a priority of objects detected

	ex: Person and phone both detected choose which to focus on
	
-Pause detection after a person is identified and action is started

	reason: no need to detect while carrying out an action, it would be wasting battery

-Action for each detection

	ex: if a cat is detected, output will be a meow
	
	ex2: if person is detected, wave hellow
	
	For no just make your actions as print statements

-Avoiding looping of actions if person or object detected remains in frame
	
	ex: if waving hello because of person detected, make sure it does it only once while a person is in frame, not continuously 

-False positives/negatives

	ex: if ML algorithm is not detected for 1 frame, it shouldn't think that the person completely disappeared and a new person came in frame
	allow some frames for buffer or verification that the object is there

