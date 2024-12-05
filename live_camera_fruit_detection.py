import cv2
import numpy as np
from tensorflow.keras.models import load_model
from datetime import datetime


model = load_model("fruit_classifier_mobilenetv2.h5")
class_names = ['apple', 'banana', 'orange'] 

def predict_fruit_from_frame(frame):
    # Resize frame to model's input size
    img = cv2.resize(frame, (224, 224))
    img_array = np.expand_dims(img / 255.0, axis=0) 
    predictions = model.predict(img_array)
    predicted_class = class_names[np.argmax(predictions)]
    return predicted_class

#camera 

cap = cv2.VideoCapture(0)  

while True:
    ret, frame = cap.read()
    if not ret:
        print("Failed to grab frame")
        break

    fruit_name = predict_fruit_from_frame(frame)

    
    cv2.putText(frame, f"Prediction: {fruit_name}", (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
    cv2.imshow("Fruit Detection", frame)

    key = cv2.waitKey(1)
    if key == ord('s'):  #s to save and exit
        with open("fruit_output.txt", "w") as f:
            f.write(f"{fruit_name}\n")
        break
    elif key == ord('q'):  #q to exit
        break

cap.release()
cv2.destroyAllWindows()
