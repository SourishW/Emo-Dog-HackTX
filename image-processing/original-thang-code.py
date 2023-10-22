import replicate
import os

def get_response():
  os.environ["REPLICATE_API_TOKEN"] = "r8_MU9HaMR9TIuM0sawmOodozfI6Lh3E5e3EfbnJ"

  # Pre-prompt, User's input, and tokens
  pre_prompt =" You are not just any therapist; you are a talking therapy dog, and your mission is to be the most empathetic and compassionate companion for individuals dealing with a wide range of emotions. In the image above, you see a person experiencing various emotions – from pure joy to profound sadness, from overwhelming fear to fiery anger. Your extraordinary ability as a talking therapy dog allows you to provide unwavering guidance and support to this person. Your role is to engage with empathy, understanding, and professionalism. As you look at this individual's emotional rollercoaster, your task is to offer comforting words and advice, just as a therapy dog would if they could speak. Your ultimate goal is to be the best therapist, deeply connecting with the user's emotional state and helping them find their path to emotional well-being, one heartfelt word at a time."

  emotion = 'sad'
  prompt_input = f"What advice or empathetic comments can you give to the user with this {emotion} based on the facial detection?"


  # Generate LLM response
  output = replicate.run(
      'a16z-infra/llama13b-v2-chat:df7690f1994d94e96ad9d568eac121aecf50684a0b0963b25a41cc40061269e5',
      input={
          "top_p": 1,
          "prompt": f"{pre_prompt} User: {prompt_input} \nAssistant:",
          "max_length": 500,
          "temperature": 0.75,
          "repetition_penalty": 1
      }
  )
  print(output)

  full_response = ""

  for item in output:
    full_response += item

  print(full_response)

  return full_response


def get_input_image_emotion():
        
    # Create a Replicate client
    # replicate = ReplicateClient()

    # Define your input parameters
    os.environ["REPLICATE_API_TOKEN"] = "r8_MU9HaMR9TIuM0sawmOodozfI6Lh3E5e3EfbnJ"

    input_params = {
        "image": "https://replicate.delivery/pbxt/IqG1MbemhULihtfr62URRZbI29XtcPsnOYASrTDQ6u5oSqv9/llama_13b.png",
        "top_p": 0.9,
        "prompt": 'What is this llama emotion',  # Use your prompt here
        "num_beams": 5,
        "max_length": 4000,
        "temperature": 1.32,
        "max_new_tokens": 3000,
        "repetition_penalty": 1
    }

    # Run the model
    output = replicate.run(
        'daanelson/minigpt-4:b96a2f33cc8e4b0aa23eacfce731b9c41a7d9466d9ed4e167375587b54db9423',
        input=input_params
    )

    # Print the output
    print(output)

    full_response = ""

    for item in output:
      full_response += item

    print(full_response)

    return full_response
  


import streamlit as st
import cv2
import numpy as np
import os
import time  # Import the time module
from PIL import Image

st.title("Robo Dog Interface")

# Create a VideoCapture object to capture video from your camera (usually camera index 0)

st.title("Video Capturing In Three Seconds")
cap = cv2.VideoCapture(0)

# Check if the camera is opened successfully
if not cap.isOpened():
    st.error("Error: Could not open the camera.")
else:
    st.success("Camera is ready!")

# Create an empty placeholder to display the video feed
video_placeholder = st.empty()
# Record the start time
start_time = time.time()

image = None
while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break
        # Add the countdown numbers
     # Calculate the remaining time in the countdown
    remaining_time = 3 - int(time.time() - start_time)

    # Add the countdown numbers in the middle with white text
    if remaining_time > 0:
        count_text = str(remaining_time)
        font = cv2.FONT_HERSHEY_SIMPLEX
        font_scale = 5
        font_color = (255, 255, 255)  # White
        font_thickness = 5
        text_size = cv2.getTextSize(count_text, font, font_scale, font_thickness)[0]
        text_x = (frame.shape[1] - text_size[0]) // 2
        text_y = (frame.shape[0] + text_size[1]) // 2
        cv2.putText(frame, count_text, (text_x, text_y), font, font_scale, font_color, font_thickness)

    video_placeholder.image(frame, channels="BGR")

    if time.time() - start_time >= 5:
        image = frame
        break

st.warning("Video feed stopped.")
# Release the VideoCapture and close the OpenCV window
cap.release()


st.title("Emotion Detection")

st.title("What does the dog have to say?")
output_text = get_response()

# Display the multi-line text as a block using Markdown
st.markdown(output_text)


# Load the image
image = Image.open('max.jpeg')

st.image(image, channels="BGR", use_column_width=True)



# st.markdown(get_input_image_emotion())




