import streamlit as st
import pandas as pd
import imageio.v2 as imageio
import numpy as np
from PIL import Image
from io import BytesIO
import matplotlib.pyplot as plt
import pickle
import os
import cv2
from streamlit_drawable_canvas import st_canvas
st.set_option('deprecation.showPyplotGlobalUse', False)


def show_image():
    img = imageio.imread('../out/brillo.ppm')
    plt.imshow(img)
    st.pyplot()

    if 'img' not in st.session_state:
        st.session_state['img'] = img

def run_filters(c, b,bw, sh,s, cp, rows, columns, color, zoom, multi):

    ps = ""
    ps3 = ""
    filters = ""

    if cp:
        filters += 'crop '
        ps += str(rows) + ' '
        ps3 += str(columns) + ' '


    if sh:
        filters += 'sharpen '
        ps += '0 '
    
    filters += 'contrast '
    ps += str(c) + ' '

    filters += 'brightness '
    ps += str(b / 100) + ' '


    if zoom:
        filters += 'zoom '
        ps += str(multi) + ' '

    ps = ps[:-1]
    ps3 = ps3[:-1]

    cmd = '.././main "' + filters + '" 1 "' + ps + '" ../imgs/ashitaka.ppm ../out/brillo.ppm '
    if ps3 != "":
        cmd += '"' + ps3 + '"'
    os.system(cmd)

   
   
# Sidebar
st.sidebar.header('Parámetros')

c = st.sidebar.slider('Contraste',-255, 255, 0, 1, '%d')
b = st.sidebar.slider('Brillo', -100, 100, 0, 1, '%d')
sh = st.sidebar.checkbox('Sharpen',value = False, key='sh')
bw = st.sidebar.checkbox('BlackWhite',value = False, key='bw')

s = 0
rows = 0
columns = 0
color = 0
margin = 0
multi = 0

st.sidebar.header('Otros')

cp = st.sidebar.checkbox('Crop',value = False, key='cp')

if cp:
    rows = st.sidebar.number_input("Filas", 1)
    columns = st.sidebar.number_input("Columnas", 1)


zoom = st.sidebar.checkbox('Zoom',value = False, key='zoom')

if zoom:
    multi = st.sidebar.number_input("Multiplicador", 2)

if st.sidebar.button('Aplicar'):
    run_filters(c, b,bw, sh,s, cp, rows, columns, color, zoom, multi)

if st.sidebar.button('Reset'):
    imageio.imwrite('../out/brillo.ppm', st.session_state['img'])

# Main layout
st.title('Filtros de imagenes')

st.subheader('Visualizador')

show_image()