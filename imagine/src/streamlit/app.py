
import streamlit as st
import pandas as pd
import imageio.v2 as imageio
import numpy as np
from PIL import Image
from io import BytesIO
import matplotlib.pyplot as plt
import os
import cv2
from streamlit_drawable_canvas import st_canvas
st.set_option('deprecation.showPyplotGlobalUse', False)


def show_image():
    img = imageio.imread('../out/salida.ppm')
    plt.imshow(img)
    st.pyplot()

    if 'img' not in st.session_state:
        st.session_state['img'] = img

def run_filters(contrast, brillo, blackw, sharpen, crop, rows, columns,zoom, multi):

    ps = ""
    ps3 = ""
    filters = ""

    if crop:
        filters += 'crop '
        ps += str(rows) + ' '
        ps3 += str(columns) + ' '

    if sharpen:
        filters += 'sharpen '
        ps += '0 '
    
    filters += 'contrast '
    ps += str(c) + ' '

    filters += 'brightness '
    ps += str(b / 100) + ' '

    if blackw:
        filters += 'blackWhite '
        ps += '0 '

    if zoom:
        filters += 'zoom '
        ps += str(multi) + ' '

    ps = ps[:-1]
    ps3 = ps3[:-1]
    
    cmd = '../main "' + filters + '" 1 "' + ps + '" ../imgs/motor.ppm ../out/salida.ppm ' + '"' + ps3 + '"'
    os.system(cmd)

   
# Sidebar
st.sidebar.header('Parámetros')

contrast = st.sidebar.slider('Contraste',-255, 255, 0, 1, '%d')
brillo = st.sidebar.slider('Brillo', -100, 100, 0, 1, '%d')
sharpen = st.sidebar.checkbox('Sharpen',value = False, key='sh')
blackw = st.sidebar.checkbox('BlackWhite',value = False, key='bw')


rows = 0
columns = 0
multi = 0

st.sidebar.header('Otros')

crop = st.sidebar.checkbox('Crop',value = False, key='crop')

if crop:
    rows = st.sidebar.number_input("Filas", 1)
    columns = st.sidebar.number_input("Columnas", 1)

zoom = st.sidebar.checkbox('Zoom',value = False, key='zoom')

if zoom:
    multi = st.sidebar.number_input("Multiplicador", 2)

if st.sidebar.button('Aplicar'):
    run_filters(contrast, brillo, blackw, sharpen, crop, rows, columns,zoom, multi)

if st.sidebar.button('Reset'):
    imageio.imwrite('../out/salida.ppm', st.session_state['img'])

# Main layout
st.title('Filtros de imagenes')

st.subheader('Visualizador')

show_image()