from tensorflow.keras.applications import MobileNetV2
from tensorflow.keras.layers import GlobalAveragePooling2D, Dense, Dropout
from tensorflow.keras.models import Sequential
from tensorflow.keras.preprocessing.image import ImageDataGenerator


train_gen = ImageDataGenerator(
    rescale=1.0/255,
    rotation_range=20,
    width_shift_range=0.2,
    height_shift_range=0.2,
    shear_range=0.2,
    zoom_range=0.2,
    horizontal_flip=True
).flow_from_directory(
    'E:/CP/CS101 Project/train', #training
    target_size=(224, 224),
    batch_size=32,
    class_mode='categorical'
)
#testing
test_gen = ImageDataGenerator(rescale=1.0/255).flow_from_directory(
    'E:/CP/CS101 Project/test',
    target_size=(224, 224),
    batch_size=32,
    class_mode='categorical'
)


base_model = MobileNetV2(weights='imagenet', include_top=False, input_shape=(224, 224, 3))
base_model.trainable = False  # Freeze the base model to prevent re-training


model = Sequential([
    base_model,
    GlobalAveragePooling2D(),  
    Dense(128, activation='relu'),  
    Dropout(0.3),  
    Dense(3, activation='softmax')
])


model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])


history = model.fit(
    train_gen,
    epochs=10,
    validation_data=test_gen
)


model.save('fruit_classifier_mobilenetv2.h5')
