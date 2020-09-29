# USAGE
# python openvino_real_time_object_detection.py --prototxt MobileNetSSD_deploy.prototxt --model MobileNetSSD_deploy.caffemodel
# test
# import the necessary packages
from imutils.video import VideoStream
from imutils.video import FPS
import numpy as np
import argparse
import imutils
import time
import cv2

# construct the argument parse and parse the arguments
ap = argparse.ArgumentParser()
#ap.add_argument("-p", "--prototxt", required=True,
#    help="path to Caffe 'deploy' prototxt file")
#ap.add_argument("-m", "--model", required=True,
#    help="path to Caffe pre-trained model")
ap.add_argument("-c", "--confidence", type=float, default=0.1,
    help="minimum probability to filter weak detections")
ap.add_argument("-u", "--movidius", type=bool, default=0,
    help="boolean indicating if the Movidius should be used")
args = vars(ap.parse_args())

# initialize the list of class labels MobileNet SSD was trained to
# detect, then generate a set of bounding box colors for each class
CLASSES = ["background", "aeroplane", "bicycle", "bird", "boat",
    "bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
    "dog", "horse", "motorbike", "person", "pottedplant", "sheep",
    "sofa", "train", "tvmonitor"]
COLORS = np.random.uniform(0, 255, size=(len(CLASSES), 3))

# load our serialized model from disk
print("[INFO] loading model...")
net = cv2.dnn.readNetFromCaffe("MobileNetSSD_deploy.prototxt", "MobileNetSSD_deploy.caffemodel")

# specify the target device as the Myriad processor on the NCS
net.setPreferableTarget(cv2.dnn.DNN_TARGET_MYRIAD)

# initialize the video stream, allow the cammera sensor to warmup,
# and initialize the FPS counter
print("[INFO] starting video stream...")
#vs = VideoStream(usePiCamera=True).start()
#vs = VideoStream(src = 0).start()
#vc = cv2.VideoCapture(0)
vc = cv2.VideoCapture("http://192.168.137.128:8090/?action=stream")
#vs = VideoStream().start()
    
time.sleep(2.0)
fps = FPS().start()

# loop over the frames from the video stream
def obj_dtct():
    
    # grab the frame from the threaded video stream and resize it
    # to have a maximum width of 400 pixels
    #frame = vs.read()
    ret, frame = vc.read()
    
    frame = imutils.resize(frame, width=400)

    # grab the frame dimensions and convert it to a blob
    (h, w) = frame.shape[:2]
    blob = cv2.dnn.blobFromImage(frame, 0.007843, (300, 300), 127.5)

    # pass the blob through the network and obtain the detections and
    # predictions
    net.setInput(blob)
    detections = net.forward()
    
    (startX, startY, endX, endY) = (0,0,0,0)

    # loop over the detections
    for i in np.arange(0, detections.shape[2]):
        # extract the confidence (i.e., probability) associated with
        # the prediction
        confidence = detections[0, 0, i, 2]

        # filter out weak detections by ensuring the `confidence` is
        # greater than the minimum confidence
        if confidence > args["confidence"]:
            
            
            # extract the index of the class label from the
            # `detections`, then compute the (x, y)-coordinates of
            # the bounding box for the object
            idx = int(detections[0, 0, i, 1])
            if CLASSES[idx]=="dog" :
                box = detections[0, 0, i, 3:7] * np.array([w, h, w, h])
                (startX, startY, endX, endY) = box.astype("int")

                # draw the prediction on the frame
            
                label = "{}: {:.2f}%".format(CLASSES[idx],
                        confidence * 100)
                cv2.rectangle(frame, (startX, startY), (endX, endY),
                        COLORS[idx], 2)
                y = startY - 15 if startY - 15 > 15 else startY + 15
                cv2.putText(frame, label, (startX, y),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, COLORS[idx], 2)
                #print("{}: {:.2f}% center x, boxsize = ( ".format(CLASSES[idx],confidence*100)+str((startX+endX)/2-200)+", "+str(endX-startX))
            

    # show the output frame"
    cv2.imshow("Cloudy", frame)
    cv2.imwrite('temp.jpg', frame)
    cv2.waitKey(1)

    # if the `q` key was pressed, break from the loop
    #if key == ord("q"):
    #    break

    # update the FPS counter
    fps.update()
    #print("dtct running ...")
    return ((startX+endX)/2-200),(endX-startX)
    #return 1,2
# stop the timer and display FPS information
def stop_dtct():
    fps.stop()
    print("[INFO] elasped time: {:.2f}".format(fps.elapsed()))
    print("[INFO] approx. FPS: {:.2f}".format(fps.fps()))

# do a bit of cleanup
    cv2.destroyAllWindows()
    vc.stop()

