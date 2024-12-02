import numpy as np
import matplotlib.pyplot as plt
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.preprocessing import image

#Loading and preprocessing dataset
train_gen = ImageDataGenerator(rescale=1.0/255).flow_from_directory(
    'E:/CP/CS101 Project/train',
    target_size=(224, 224),
    batch_size=32,
    class_mode='categorical'
)

test_gen = ImageDataGenerator(rescale=1.0/255).flow_from_directory(
    'E:/CP/CS101 Project/test', 
    target_size=(224, 224),
    batch_size=32,
    class_mode='categorical'
)

#Model train
model = Sequential([
    Conv2D(32, (3, 3), activation='relu', input_shape=(224, 224, 3)),
    MaxPooling2D((2, 2)),
    Conv2D(64, (3, 3), activation='relu'),
    MaxPooling2D((2, 2)),
    Flatten(),
    Dense(128, activation='relu'),
    Dense(3, activation='softmax')  # 3 classes: apple, banana, orange
])


model.compile(optimizer='adam',
              loss='categorical_crossentropy',
              metrics=['accuracy'])

#Training
history = model.fit(
    train_gen,
    epochs=10,  
    validation_data=test_gen
)

#Accuracy checks
loss, accuracy = model.evaluate(test_gen)
print(f"Test Accuracy: {accuracy * 100:.2f}%")


model.save('fruit_classifier.h5')
print("Model saved as fruit_classifier.h5")

#Predict functions
def predict_fruit(image_path):
    img = image.load_img(image_path, target_size=(224, 224))
    img_array = image.img_to_array(img) / 255.0 
    img_array = np.expand_dims(img_array, axis=0) 

    predictions = model.predict(img_array)
    class_names = ['apple', 'banana', 'orange'] 
    predicted_class = class_names[np.argmax(predictions)]
    print(f"Predicted: {predicted_class}")


predict_fruit("E:\99_100.jpg")

plt.plot(history.history['accuracy'], label='Training Accuracy')
plt.plot(history.history['val_accuracy'], label='Validation Accuracy')
plt.legend()
plt.title('Model Accuracy')
plt.show()

plt.plot(history.history['loss'], label='Training Loss')
plt.plot(history.history['val_loss'], label='Validation Loss')
plt.legend()
plt.title('Model Loss')
plt.show()