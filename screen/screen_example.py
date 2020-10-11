import webview
import multiprocessing
import time
import cv2
import numpy as np


#Robot's screen will be displaying instagram feed(although using twitter feed to test)
#It will also still run voice detection in the background.
#justprint(); is a placeholder function for the voice dection, but it has to be running
#to change window to display video or feed accordingly. 


def tweetopen():
#Create window named Robotscreen that displays twitter page with 1024x600 resolution
#fullscreen

    window =  webview.create_window('Robotscreen',
                          html='<a class="twitter-timeline" data-lang="en" data-width="950" data-height="768" data-theme="dark" href="https://twitter.com/utrgv?ref_src=twsrc%5Etfw">Tweets by utrgv</a> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>',
                          fullscreen=True)

#start window
    webview.start()


#just a test function 
def justprint():
    for i in range(10):
        time.sleep(1)
        print('doing stuff after',i+1,'seconds')
        
        

#video player
def video_fullscreen(winname,vid):
    cv2.namedWindow(winname,cv2.WINDOW_NORMAL)
    cv2.setWindowProperty('screen',cv2.WND_PROP_FULLSCREEN,cv2.WINDOW_FULLSCREEN)
    if (vid.isOpened()== False):  
        print("Error opening video  file") 

    while(vid.isOpened()): 
        ret, frame = vid.read() 
        if ret == True: 
            cv2.imshow('screen', frame) 
            if cv2.waitKey(25) & 0xFF == ord('q'): 
                break
        else:  
            break
    vid.release() 
    cv2.destroyAllWindows() 



        
#select video to play
#video 1 is named hellohuman.mp4
#video 2 is IEEEBSB.mp4
#just a test, input will be replaced by voice recognition keyword
k =input('Which video to play?')
if k=="hello":
	p=cv2.VideoCapture('hellohuman.mp4') 
else:
	p=cv2.VideoCapture('IEEEBSB.mp4')


        
        
        
#multiprocessing with window   
#running both codes at once, window is no longer non-blocking     
process = multiprocessing.Process(target=tweetopen)
process2 = multiprocessing.Process(target=justprint)
process3=multiprocessing.Process(target=video_fullscreen,args=('swag',p))
if __name__ == '__main__':
    process.start()
    process2.start()
    print('waiting 10 seconds')
    time.sleep(10)
    process.terminate()
    process3.start()
    time.sleep(10)
    process3.terminate()
