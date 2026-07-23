using System;
using System.Collections.Generic;
using System.Drawing.Imaging;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CX900
{
    internal class Image2Bin
    {
        private static byte[] getRevertArrays(byte[] inArray, int count)
        {
            if (inArray == null)
                return (byte[])null;
            byte[] revertArrays = new byte[inArray.Length];
            int length = inArray.Length;
            int num = length % count;
            for (int index1 = 0; index1 < length - num; index1 += count)
            {
                for (int index2 = 0; index2 < count; ++index2)
                    revertArrays[index1 + index2] = inArray[index1 + count - index2 - 1];
            }
            for (int index = 0; index < num; ++index)
                revertArrays[length - num + index] = inArray[length - index - 1];
            return revertArrays;
        }

        private static Color[] RGBs2Colors(byte[] rgbs, bool RGB565)
        {
            int index1 = 0;
            int length = RGB565 ? rgbs.Length / 2 : rgbs.Length / 3;
            Color[] colorArray = new Color[length];
            if (RGB565)
            {
                for (int index2 = 0; index2 < length; ++index2)
                {
                    int[] numArray = new int[3];
                    byte[] destinationArray = new byte[2];
                    Array.Copy((Array)rgbs, index2 * 2, (Array)destinationArray, 0, 2);
                    int int16 = (int)BitConverter.ToInt16(new byte[2]
                    {
            destinationArray[1],
            destinationArray[0]
                    }, 0);
                    numArray[2] = (int16 & 63488) >> 11;
                    numArray[1] = (int16 & 2016) >> 5;
                    numArray[0] = int16 & 31;
                    numArray[2] <<= 3;
                    numArray[1] <<= 2;
                    numArray[0] <<= 3;
                    colorArray[index1] = Color.FromArgb(numArray[2], numArray[1], numArray[0]);
                    ++index1;
                }
            }
            else
            {
                for (int index3 = 0; index3 < length; ++index3)
                {
                    int[] numArray = new int[3];
                    byte[] destinationArray = new byte[4];
                    Array.Copy((Array)rgbs, index3 * 3, (Array)destinationArray, 0, 3);
                    int int32 = BitConverter.ToInt32(destinationArray, 0);
                    numArray[0] = (int32 & 16711680) >> 16;
                    numArray[1] = (int32 & 65280) >> 8;
                    numArray[2] = int32 & (int)byte.MaxValue;
                    colorArray[index1] = Color.FromArgb(numArray[2], numArray[1], numArray[0]);
                    ++index1;
                }
            }
            return colorArray;
        }

        private static int rgb565PFromColor(Color color) => (int)color.R >> 3 << 11 | (int)color.G >> 2 << 5 | (int)color.B >> 3;

        private static byte[] GetImagePixel(Bitmap img, bool RGB565)
        {
            byte[] inArray1 = new byte[img.Width * img.Height * 3];
            byte[] inArray2 = new byte[img.Width * img.Height * 2];
            int index1 = 0;
            int index2 = 0;
            int height = img.Height;
            int width = img.Width;
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    Color pixel = img.GetPixel(x, y);
                    inArray1[index1] = pixel.R;
                    inArray1[index1 + 1] = pixel.G;
                    inArray1[index1 + 2] = pixel.B;
                    byte[] bytes = BitConverter.GetBytes(rgb565PFromColor(pixel));
                    inArray2[index2] = bytes[1];
                    inArray2[index2 + 1] = bytes[0];
                    index2 += 2;
                    index1 += 3;
                }
            }
            return !RGB565 ? getRevertArrays(inArray1, 4) : getRevertArrays(inArray2, 4);
        }

        //public static byte[] bytes1(Bitmap bmg, bool RGB565) => GetImagePixel(bmg, RGB565);

        public static Bitmap bin2img(byte[] bin, int w, int h, bool RGB565)
        {
            bin = getRevertArrays(bin, 4);
            return Color2Bmp(RGBs2Colors(bin, RGB565), w, h);
        }

        public static Bitmap Color2Bmp(Color[] colors, int width, int height)
        {
            Bitmap bitmap = new Bitmap(width, height, PixelFormat.Format24bppRgb);
            int num = height * width;
            for (int index = 0; index < num; ++index)
                bitmap.SetPixel(index % width, index / width, colors[index]);
            return bitmap;
        }
    }
}
