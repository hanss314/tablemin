import sys
import math
from PIL import Image, ImageDraw

WIDTH=1366
HEIGHT=768

colors = [
    False, True, False, False, True, False, 
    True, False, False, True, False, True
]

step = 2**(1/12)

def create_image(low, high, name=None):
    l, h = low, high
    img = Image.new('RGB', (WIDTH, HEIGHT), color=(255,255,255))
    draw = ImageDraw.Draw(img)
    note = 440.0
    
    low = math.log(low*step/27.5, step)
    high = math.log(high*step/27.5, step)
 
    start = int(low)
    end = int(high)
    startx = (start-low)*WIDTH/(high-low)
    endx = (high-low)*WIDTH/(high-low)
    stepwidth = (endx-startx)/(end-start-1)

    print(low, high)
    for i in range(start, end):
        x = (i-start)*stepwidth+0.5*stepwidth
        black = colors[i%12]
        if black:
            draw.rectangle(
                [x, 0, x-stepwidth, HEIGHT],
                fill=(0,0,0), outline=(255,255,255)
            )
        else:
            draw.line(
                [x, 0, x, HEIGHT],
                fill=(0,0,0), width=1
            )

    if name is None:
        name = f"{l:.01f}-{h:.01f}".replace('.', '_')
        name = f'{name}.png'

    img.save(name)
    return name


if __name__ == '__main__':
    create_image(float(sys.argv[1]), float(sys.argv[2]))


