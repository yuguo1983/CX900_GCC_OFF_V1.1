using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace CX900
{
    public class MakeImage
    {

        public static int ColorMode = 24;

        public static Image make_CIE1931(int x, int y)
        {
            Color[] colors = new Color[x * y];
            //for (int index1 = 0; index1 < y; ++index1)
            //{
            //    for (int index2 = 0; index2 < x; ++index2)
            //        colors[index1 * x + index2] = new Color_Point()
            //        {
            //            sx = ((double)index2 / 1000.0),
            //            sy = ((double)index1 / 1000.0),
            //            Lv = 0.0
            //        }.toColor();
            //}
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }

        public static Image makeColorImg(Color index, int x, int y)
        {
            Color[] colors = new Color[x * y];
            int num = x * y;
            for (int index1 = 0; index1 < num; ++index1)
                colors[index1] = index;
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }

        /// <summary>
        /// 把文字转换才Bitmap
        /// </summary>
        /// <param name="text"></param>
        /// <param name="font"></param>
        /// <param name="rect">用于输出的矩形，文字在这个矩形内显示，为空时自动计算</param>
        /// <param name="fontcolor">字体颜色</param>
        /// <param name="backColor">背景颜色</param>
        /// <returns></returns>
        public static Bitmap TextToBitmap(string text, Font font, Rectangle rect, Color fontcolor, Color backColor)
        {
            Graphics g;
            Bitmap bmp;
            StringFormat format = new StringFormat(StringFormatFlags.NoClip);
            if (rect == Rectangle.Empty)
            {
                bmp = new Bitmap(1, 1);
                g = Graphics.FromImage(bmp);

                //计算绘制文字所需的区域大小（根据宽度计算长度），重新创建矩形区域绘图
                SizeF sizef = g.MeasureString(text, font, PointF.Empty, format);

                int width = (int)(sizef.Width + 1);
                int height = (int)(sizef.Height + 1);
                rect = new Rectangle(0, 0, 256, 448);
                bmp.Dispose();

                bmp = new Bitmap(256, 448);
            }
            else
            {
                bmp = new Bitmap(rect.Width, rect.Height);
            }

            g = Graphics.FromImage(bmp);

            //使用ClearType字体功能
            g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.ClearTypeGridFit;
            SolidBrush solidBrush = new SolidBrush(fontcolor);
            g.FillRectangle(new SolidBrush(backColor), rect);
            StringFormat sf = new StringFormat();
            sf.LineAlignment = StringAlignment.Center;
            sf.Alignment = StringAlignment.Center;
            g.DrawString(text, font, solidBrush, rect, sf);
            return bmp;
        }


        public static Image makeFrameImg(Color bColor, Color fColor, int x, int y)
        {
            Color[] colors = new Color[x * y];
            int num1 = x * y;
            for (int index1 = 0; index1 < y; ++index1)
            {
                if (index1 == 0 || index1 == y - 1)
                {
                    for (int index2 = 0; index2 < x; ++index2)
                        colors[index1 * x + index2] = bColor;
                }
                else
                {
                    for (int index3 = 0; index3 < x; ++index3)
                    {
                        int num2 = index3 == 0 ? 1 : (index3 == x - 1 ? 1 : 0);
                        colors[index1 * x + index3] = num2 == 0 ? fColor : bColor;
                    }
                }
            }
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }
        public static Image makeCrossTalkImg(Color bColor, Color fColor, int x, int y)
        {
            Color[] colors = new Color[x * y];
            int num1 = x * y;
            for (int index1 = 0; index1 < y; ++index1)
            {
                if (index1 < y / 3 || index1 > y - y / 3)
                {
                    for (int index2 = 0; index2 < x; ++index2)
                        colors[index1 * x + index2] = bColor;
                }
                else
                {
                    for (int index3 = 0; index3 < x; ++index3)
                    {
                        int num2 = index3 < x / 3 ? 1 : (index3 > x - x / 3 ? 1 : 0);
                        colors[index1 * x + index3] = num2 == 0 ? fColor : bColor;
                    }
                }
            }
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }
        public static Image makeGrayImg(int index, int level, int x, int y)
        {
            Color[] colorArray = new Color[x * y];
            int num = x * y;
            return index != 0 ? MakeImage.makeGrayHImg(level, x, y) : MakeImage.makeGrayVImg(level, x, y);
        }

        private static Image makeGrayHImg(int level, int x, int y)
        {
            ++level;
            int num1 = (int)((double)y / (double)level);
            int num2 = (y - num1 * (level - 2)) / 2;
            int num3 = y - num1 * (level - 2) - num2;
            int num4 = (int)((double)x / (double)level);
            int num5 = (x - num4 * (level - 2)) / 2;
            int num6 = x - num4 * (level - 2) - num5;
            int num7 = MakeImage.ColorMode == 24 ? 256 : 32;
            level = level > num7 ? num7 : level;
            double num8 = (double)(int)((double)num7 / (double)level);
            Color[] colors = new Color[x * y];
            int num9 = 0;
            for (int index1 = 0; index1 < y; ++index1)
            {
                for (int index2 = 0; index2 < num5; ++index2)
                    colors[num9++] = Color.Black;
                for (int index3 = 1; index3 < level - 1; ++index3)
                {
                    for (int index4 = 0; index4 < num4; ++index4)
                    {
                        int num10 = (int)((double)index3 * num8);
                        int num11 = num10 > (int)byte.MaxValue ? (int)byte.MaxValue : num10;
                        Color color = Color.FromArgb((int)byte.MaxValue, num11, num11, num11);
                        colors[num9++] = color;
                    }
                }
                for (int index5 = 0; index5 < num6; ++index5)
                    colors[num9++] = Color.White;
            }
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }

        public static Image makeColorGrayLevelImg(int hv, byte mode, byte level, int x, int y) => hv == 0 ? MakeImage.makeGrayHImg(mode, (int)level, x, y) : MakeImage.makeGrayVImg(mode, (int)level, x, y);

        private static Image makeGrayHImg(byte mode, int level, int x, int y)
        {
            ++level;
            int num1 = (int)((double)y / (double)level);
            int num2 = (y - num1 * (level - 2)) / 2;
            int num3 = y - num1 * (level - 2) - num2;
            int num4 = (int)((double)x / (double)level);
            int num5 = (x - num4 * (level - 2)) / 2;
            int num6 = x - num4 * (level - 2) - num5;
            int num7 = MakeImage.ColorMode == 24 ? 256 : 32;
            level = level > num7 ? num7 : level;
            double num8 = (double)(int)((double)num7 / (double)level);
            Color[] colors = new Color[x * y];
            int num9 = 0;
            for (int index1 = 0; index1 < y; ++index1)
            {
                for (int index2 = 0; index2 < num5; ++index2)
                    colors[num9++] = Color.Black;
                for (int index3 = 1; index3 < level - 1; ++index3)
                {
                    for (int index4 = 0; index4 < num4; ++index4)
                    {
                        int num10 = (int)((double)index3 * num8);
                        int num11 = num10 > (int)byte.MaxValue ? (int)byte.MaxValue : num10;
                        Color black = Color.Black;
                        Color color;
                        switch (mode)
                        {
                            case 1:
                                int num12 = y / 4;
                                switch (index1 / num12)
                                {
                                    case 0:
                                        color = Color.FromArgb((int)byte.MaxValue, num11, 0, 0);
                                        break;
                                    case 1:
                                        color = Color.FromArgb((int)byte.MaxValue, 0, num11, 0);
                                        break;
                                    case 2:
                                        color = Color.FromArgb((int)byte.MaxValue, 0, 0, num11);
                                        break;
                                    default:
                                        color = Color.FromArgb((int)byte.MaxValue, num11, num11, num11);
                                        break;
                                }
                                break;
                            case 2:
                                int num13 = y / 7;
                                switch (index1 / num13)
                                {
                                    case 0:
                                        color = Color.FromArgb((int)byte.MaxValue, num11, 0, 0);
                                        break;
                                    case 1:
                                        color = Color.FromArgb((int)byte.MaxValue, 0, num11, 0);
                                        break;
                                    case 2:
                                        color = Color.FromArgb((int)byte.MaxValue, 0, 0, num11);
                                        break;
                                    case 3:
                                        color = Color.FromArgb((int)byte.MaxValue, num11, num11, 0);
                                        break;
                                    case 4:
                                        color = Color.FromArgb((int)byte.MaxValue, num11, 0, num11);
                                        break;
                                    case 5:
                                        color = Color.FromArgb((int)byte.MaxValue, 0, num11, num11);
                                        break;
                                    default:
                                        color = Color.FromArgb((int)byte.MaxValue, num11, num11, num11);
                                        break;
                                }
                                break;
                            default:
                                color = Color.FromArgb((int)byte.MaxValue, num11, num11, num11);
                                break;
                        }
                        colors[num9++] = color;
                    }
                }
                for (int index5 = 0; index5 < num6; ++index5)
                    colors[num9++] = Color.White;
            }
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }

        public static Image MakeColorBarRow(int Num, int Width, int Height)
        {
            Color color;
            Bitmap bmp = new Bitmap(256, 448);
            Image image = null;
            for (int i = 0; i < Num; i++)
            {
                switch (i)
                {
                    case 0: color = Color.FromArgb(0x00, 0x00, 0x00); break;
                    case 1: color = Color.FromArgb(0x00, 0x00, 0xff); break;
                    case 2: color = Color.FromArgb(0x00, 0xff, 0x00); break;
                    case 3: color = Color.FromArgb(0xff, 0x00, 0x00); break;
                    case 4: color = Color.FromArgb(0xff, 0x00, 0xff); break;
                    case 5: color = Color.FromArgb(0x00, 0xff, 0xff); break;
                    case 6: color = Color.FromArgb(0xff, 0xff, 0x00); break;
                    case 7: color = Color.FromArgb(0xff, 0xff, 0xff); break;
                    case 8: color = Color.FromArgb(0xff, 0xf0, 0x00); break;
                    case 9: color = Color.FromArgb(0xf0, 0x0f, 0xff); break;
                    case 10: color = Color.FromArgb(0xf0, 0xf0, 0x0f); break;
                    case 11: color = Color.FromArgb(0xf0, 0xf0, 0x0f); break;
                    case 12: color = Color.FromArgb(0xf0, 0xf0, 0xff); break;
                    case 13: color = Color.FromArgb(0xff, 0xf0, 0xff); break;
                    case 14: color = Color.FromArgb(0xf0, 0xff, 0x0f); break;
                    case 15: color = Color.FromArgb(0xf0, 0x0f, 0x0f); break;
                    default: color = Color.Black; break;
                }
                RectangleF[] rec = new RectangleF[Num];
                rec[i].Size = new Size(Width, (i + 1) * Height / Num);
                rec[i].Location = new Point(0, i * Height / Num);
                Graphics g = Graphics.FromImage(bmp);
                SolidBrush brush = new SolidBrush(color);
                g.FillRectangle(brush, rec[i]);

            }
            image = bmp;
            return image;
        }

        public static Image MakeColorBarCol(int Num, int Width, int Height)
        {
            Color color;
            Bitmap bmp = new Bitmap(256, 448);
            Image image = null;
            for (int i = 0; i < Num; i++)
            {
                switch (i)
                {
                    case 0: color = Color.FromArgb(0x00, 0x00, 0x00); break;
                    case 1: color = Color.FromArgb(0x00, 0x00, 0xff); break;
                    case 2: color = Color.FromArgb(0x00, 0xff, 0x00); break;
                    case 3: color = Color.FromArgb(0xff, 0x00, 0x00); break;
                    case 4: color = Color.FromArgb(0xff, 0x00, 0xff); break;
                    case 5: color = Color.FromArgb(0x00, 0xff, 0xff); break;
                    case 6: color = Color.FromArgb(0xff, 0xff, 0x00); break;
                    case 7: color = Color.FromArgb(0xff, 0xff, 0xff); break;
                    case 8: color = Color.FromArgb(0xff, 0xf0, 0x00); break;
                    case 9: color = Color.FromArgb(0xf0, 0x0f, 0xff); break;
                    case 10: color = Color.FromArgb(0xf0, 0xf0, 0x0f); break;
                    case 11: color = Color.FromArgb(0xf0, 0xf0, 0x0f); break;
                    case 12: color = Color.FromArgb(0xf0, 0xf0, 0xff); break;
                    case 13: color = Color.FromArgb(0xff, 0xf0, 0xff); break;
                    case 14: color = Color.FromArgb(0xf0, 0xff, 0x0f); break;
                    case 15: color = Color.FromArgb(0xf0, 0x0f, 0x0f); break;
                    default: color = Color.Black; break;
                }
                RectangleF[] rec = new RectangleF[Num];
                rec[i].Size = new Size((i + 1) * Width / Num, Height);
                rec[i].Location = new Point(i * Width / Num, 0);
                Graphics g = Graphics.FromImage(bmp);
                SolidBrush brush = new SolidBrush(color);
                g.FillRectangle(brush, rec[i]);

            }
            image = bmp;
            return image;
        }

        public static Image MakeGradCol(Color color, int div)
        {
            Bitmap bmp = new Bitmap(256, 448);
            Image image = null;
            int temp, tempc;
            float inc;
            byte red, red1;
            byte green, green1;
            byte blue, blue1;
            int Width = 256;
            int Height = 448;
            red = color.R;
            green = color.G;
            blue = color.B;
            inc = Width / div;
            tempc = 0;
            try
            {
                for (temp = 0; tempc < Width; temp++)
                {
                    tempc = Convert.ToInt32(temp * inc);
                    red1 = Convert.ToByte(tempc * red / Width);
                    green1 = Convert.ToByte((tempc * green) / Width);
                    blue1 = Convert.ToByte((tempc * blue) / Width);

                    RectangleF[] rec = new RectangleF[Width * 2];
                    Color colorvalue = Color.FromArgb(red1, green1, blue1);
                    rec[temp].Size = new Size(Convert.ToInt32(tempc + inc), Height);
                    rec[temp].Location = new Point(tempc, 0);
                    Graphics g = Graphics.FromImage(bmp);
                    SolidBrush brush = new SolidBrush(colorvalue);
                    g.FillRectangle(brush, rec[temp]);

                }
            }
            catch (Exception e)
            {

                Debug.WriteLine(e.Message);
            }

            image = bmp;
            return image;
        }

        public static Image MakeGradRow(Color color, int div)
        {
            Bitmap bmp = new Bitmap(256, 448);
            Image image = null;
            int temp, tempc;
            float inc;
            byte red, red1;
            byte green, green1;
            byte blue, blue1;
            int Width = 256;
            int Height = 448;
            red = color.R;
            green = color.G;
            blue = color.B;
            inc = Height / div;
            tempc = 0;
            try
            {
                for (temp = 0; tempc < Height; temp++)
                {
                    tempc = Convert.ToInt32(temp * inc);
                    red1 = (byte)Convert.ToByte((tempc * red / Height) > 255 ? 255 : ((float)tempc * red / Height));
                    green1 = Convert.ToByte(((tempc * green) / Height) > 255 ? 255 : ((float)(tempc * green) / Height));
                    blue1 = Convert.ToByte(((tempc * blue) / Height) > 255 ? 255 : ((float)(tempc * blue) / Height));

                    RectangleF[] rec = new RectangleF[Height * 2];
                    Color colorvalue = Color.FromArgb(red1, green1, blue1);
                    rec[temp].Size = new Size(Width, Convert.ToInt32(tempc + inc));
                    rec[temp].Location = new Point(0, tempc);
                    Graphics g = Graphics.FromImage(bmp);
                    SolidBrush brush = new SolidBrush(colorvalue);
                    g.FillRectangle(brush, rec[temp]);

                }

            }
            catch (Exception e)
            {

                Debug.WriteLine(e.Message);
            }
            image = bmp;
            return image;
        }
        public static Image makeGrayVImg(int level, int x, int y)
        {
            ++level;
            int num1 = (int)((double)y / (double)level);
            int num2 = (y - num1 * (level - 2)) / 2;
            int num3 = y - num1 * (level - 2) - num2;
            int num4 = (int)((double)x / (double)level);
            int num5 = (x - num4 * (level - 2)) / 2;
            int num6 = x - num4 * (level - 2) - num5;
            int num7 = MakeImage.ColorMode == 24 ? 256 : 32;
            level = level > num7 ? num7 : level;
            double num8 = (double)(int)((double)num7 / (double)level);
            Color[] colors = new Color[x * y];
            int num9 = 0;
            for (int index1 = 0; index1 < num2; ++index1)
            {
                for (int index2 = 0; index2 < x; ++index2)
                    colors[num9++] = Color.Black;
            }
            for (int index3 = 1; index3 < level - 1; ++index3)
            {
                for (int index4 = 0; index4 < num1; ++index4)
                {
                    for (int index5 = 0; index5 < x; ++index5)
                    {
                        int num10 = (int)((double)index3 * num8);
                        int num11 = num10 > (int)byte.MaxValue ? (int)byte.MaxValue : num10;
                        Color color = Color.FromArgb((int)byte.MaxValue, num11, num11, num11);
                        colors[num9++] = color;
                    }
                }
            }
            for (int index6 = 0; index6 < num2; ++index6)
            {
                for (int index7 = 0; index7 < x; ++index7)
                    colors[num9++] = Color.White;
            }
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }

        private static Image makeGrayVImg(byte mode, int level, int x, int y)
        {
            ++level;
            int num1 = (int)((double)y / (double)level);
            int num2 = (y - num1 * (level - 2)) / 2;
            int num3 = y - num1 * (level - 2) - num2;
            int num4 = (int)((double)x / (double)level);
            int num5 = (x - num4 * (level - 2)) / 2;
            int num6 = x - num4 * (level - 2) - num5;
            int num7 = MakeImage.ColorMode == 24 ? 256 : 32;
            level = level > num7 ? num7 : level;
            double num8 = (double)(int)((double)num7 / (double)level);
            Color[] colors = new Color[x * y];
            int num9 = 0;
            for (int index1 = 0; index1 < num2; ++index1)
            {
                for (int index2 = 0; index2 < x; ++index2)
                    colors[num9++] = Color.Black;
            }
            for (int index3 = 1; index3 < level - 1; ++index3)
            {
                for (int index4 = 0; index4 < num1; ++index4)
                {
                    for (int index5 = 0; index5 < x; ++index5)
                    {
                        int num10 = (int)((double)index3 * num8);
                        int num11 = num10 > (int)byte.MaxValue ? (int)byte.MaxValue : num10;
                        Color black = Color.Black;
                        Color color;
                        switch (mode)
                        {
                            case 1:
                                int num12 = x / 4;
                                switch (index5 / num12)
                                {
                                    case 0:
                                        color = Color.FromArgb((int)byte.MaxValue, num11, 0, 0);
                                        break;
                                    case 1:
                                        color = Color.FromArgb((int)byte.MaxValue, 0, num11, 0);
                                        break;
                                    case 2:
                                        color = Color.FromArgb((int)byte.MaxValue, 0, 0, num11);
                                        break;
                                    default:
                                        color = Color.FromArgb((int)byte.MaxValue, num11, num11, num11);
                                        break;
                                }
                                break;
                            case 2:
                                int num13 = x / 7;
                                switch (index5 / num13)
                                {
                                    case 0:
                                        color = Color.FromArgb((int)byte.MaxValue, num11, 0, 0);
                                        break;
                                    case 1:
                                        color = Color.FromArgb((int)byte.MaxValue, 0, num11, 0);
                                        break;
                                    case 2:
                                        color = Color.FromArgb((int)byte.MaxValue, 0, 0, num11);
                                        break;
                                    case 3:
                                        color = Color.FromArgb((int)byte.MaxValue, num11, num11, 0);
                                        break;
                                    case 4:
                                        color = Color.FromArgb((int)byte.MaxValue, num11, 0, num11);
                                        break;
                                    case 5:
                                        color = Color.FromArgb((int)byte.MaxValue, 0, num11, num11);
                                        break;
                                    default:
                                        color = Color.FromArgb((int)byte.MaxValue, num11, num11, num11);
                                        break;
                                }
                                break;
                            default:
                                color = Color.FromArgb((int)byte.MaxValue, num11, num11, num11);
                                break;
                        }
                        colors[num9++] = color;
                    }
                }
            }
            for (int index6 = 0; index6 < num2; ++index6)
            {
                for (int index7 = 0; index7 < x; ++index7)
                    colors[num9++] = Color.White;
            }
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }

        public static Image makeFlickerImg(int index, Color bColor, Color fColor, int x, int y)
        {
            Image image = (Image)null;
            switch (index)
            {
                case 0:
                    image = MakeImage.makeLineFlicerImg(bColor, fColor, x, y);
                    break;
                case 1:
                    image = MakeImage.make1DotFlickerImg(bColor, fColor, x, y);
                    break;
                case 2:
                    image = MakeImage.make2DotFlickerImg(bColor, fColor, x, y);
                    break;
            }
            return image;
        }

        public static Image makeLineFlicerImg(Color bColor, Color fColor, int x, int y)
        {
            Color[] colors = new Color[x * y];
            int num = 0;
            for (int index1 = 0; index1 < y; ++index1)
            {
                for (int index2 = 0; index2 < x; ++index2)
                    colors[num++] = index2 % 2 != 0 ? fColor : bColor;
            }
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }

        private static Image make1DotFlickerImg(Color bColor, Color fColor, int x, int y)
        {
            Color[] colors = new Color[x * y];
            int num = 0;
            for (int index1 = 0; index1 < y; ++index1)
            {
                for (int index2 = 0; index2 < x; ++index2)
                    colors[num++] = index1 % 2 != 0 ? (index2 % 2 != 0 ? bColor : fColor) : (index2 % 2 != 0 ? fColor : bColor);
            }
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }

        public static Image make2DotFlickerImg(Color bColor, Color fColor, int x, int y)
        {
            Color[] colors = new Color[x * y];
            int num = 0;
            for (int index1 = 0; index1 < y; ++index1)
            {
                for (int index2 = 0; index2 < x; ++index2)
                    colors[num++] = index1 % 4 >= 2 ? (index2 % 2 != 0 ? bColor : fColor) : (index2 % 2 != 0 ? fColor : bColor);
            }
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }

        public static Image makeCrossTalkImg(
          int index,
          Color bColor,
          Color fColor,
          Color tColor,
          int x,
          int y,
          int x1,
          int y1,
          int xw1,
          int yh1,
          int x2,
          int y2,
          int xw2,
          int yh2)
        {
            Color[] colors = new Color[x * y];
            int num1 = 0;
            if (x < x1 + xw1 || x < x2 + xw2 || y < y1 + yh1 || y < y2 + yh2)
                return (Image)null;
            bool flag1;
            switch (index)
            {
                case 0:
                    for (int index1 = 0; index1 < y; ++index1)
                    {
                        for (int index2 = 0; index2 < x; ++index2)
                        {
                            int num2 = index1 < y / 3 || index1 > y / 3 * 2 || index2 < x / 3 ? 0 : (index2 <= x / 3 * 2 ? 1 : 0);
                            colors[num1++] = num2 == 0 ? tColor : fColor;
                        }
                    }
                    break;
                case 1:
                    int num3 = x / 8;
                    int num4 = y / 10;
                    flag1 = false;
                    for (int index3 = 0; index3 < y; ++index3)
                    {
                        for (int index4 = 0; index4 < x; ++index4)
                        {
                            bool flag2 = index3 >= num4 && index4 >= num3 && index3 <= num4 * 4 && index4 <= num3 * 2 || index3 >= num4 * 2 && index4 >= num3 * 2 && index3 <= num4 * 3 && index4 <= num3 * 6 || index3 >= num4 && index4 >= num3 * 6 && index3 <= num4 * 4 && index4 <= num3 * 7 || index3 >= num4 * 6 && index4 >= num3 && index3 <= num4 * 9 && index4 <= num3 * 2 || index3 >= num4 * 7 && index4 >= num3 * 2 && index3 <= num4 * 8 && index4 <= num3 * 6 || index3 >= num4 * 6 && index4 >= num3 * 6 && index3 <= num4 * 9 && index4 <= num3 * 7;
                            colors[num1++] = index3 >= y / 2 ? (!flag2 ? fColor : tColor) : (!flag2 ? tColor : fColor);
                        }
                    }
                    break;
                case 2:
                    int num5 = x / 8;
                    int num6 = y / 10;
                    flag1 = false;
                    for (int index5 = 0; index5 < y; ++index5)
                    {
                        for (int index6 = 0; index6 < x; ++index6)
                        {
                            bool flag3 = index5 >= num6 && index6 >= num5 && index5 <= num6 * 4 && index6 <= num5 * 2 || index5 >= num6 * 2 && index6 >= num5 * 2 && index5 <= num6 * 3 && index6 <= num5 * 6 || index5 >= num6 && index6 >= num5 * 6 && index5 <= num6 * 4 && index6 <= num5 * 7 || index5 >= num6 * 6 && index6 >= num5 && index5 <= num6 * 9 && index6 <= num5 * 2 || index5 >= num6 * 7 && index6 >= num5 * 2 && index5 <= num6 * 8 && index6 <= num5 * 6 || index5 >= num6 * 6 && index6 >= num5 * 6 && index5 <= num6 * 9 && index6 <= num5 * 7;
                            colors[num1++] = index5 >= y / 2 ? (!flag3 ? bColor : tColor) : (!flag3 ? bColor : fColor);
                        }
                    }
                    break;
            }
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }

        public static Image makeColorTableImg(int index, Color[] color, int x, int y)
        {
            Color[] colors = new Color[x * y];
            int length = color.Length;
            int num1 = y / length;
            int num2 = y % length;
            int num3 = x / length;
            int num4 = x % length;
            int num5 = 0;
            switch (index)
            {
                case 0:
                    for (int index1 = 0; index1 < length; ++index1)
                    {
                        for (int index2 = 0; index2 < num1; ++index2)
                        {
                            for (int index3 = 0; index3 < x; ++index3)
                                colors[num5++] = color[index1];
                        }
                    }
                    for (int index4 = 0; index4 < num2; ++index4)
                    {
                        for (int index5 = 0; index5 < x; ++index5)
                            colors[num5++] = color[length - 1];
                    }
                    break;
                case 1:
                    for (int index6 = 0; index6 < y; ++index6)
                    {
                        for (int index7 = 0; index7 < length; ++index7)
                        {
                            for (int index8 = 0; index8 < num3; ++index8)
                                colors[num5++] = color[index7];
                            if (index7 == length - 1)
                            {
                                for (int index9 = 0; index9 < num4; ++index9)
                                    colors[num5++] = color[length - 1];
                            }
                        }
                    }
                    break;
            }
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }

        public static Image makeWBImg(
          int row,
          int column,
          Color bColor,
          Color fColor,
          int x,
          int y)
        {
            Color[] colors = new Color[x * y];
            int num1 = 0;
            int num2 = x / column;
            int num3 = y / (row == 0 ? column : row);
            row = row == 0 ? column : row;
            int num4 = x % column;
            int num5 = y % row;
            for (int index1 = 0; index1 < row; ++index1)
            {
                for (int index2 = 0; index2 < num3; ++index2)
                {
                    for (int index3 = 0; index3 < column; ++index3)
                    {
                        for (int index4 = 0; index4 < num2; ++index4)
                            colors[num1++] = index1 % 2 != 0 ? (index3 % 2 == 0 ? fColor : bColor) : (index3 % 2 == 0 ? bColor : fColor);
                        if (index3 == column - 1)
                        {
                            for (int index5 = 0; index5 < num4; ++index5)
                                colors[num1++] = index1 % 2 != 0 ? (index3 % 2 == 0 ? fColor : bColor) : (index3 % 2 == 0 ? bColor : fColor);
                        }
                    }
                }
                if (index1 == row - 1)
                {
                    for (int index6 = 0; index6 < num5; ++index6)
                    {
                        for (int index7 = 0; index7 < column; ++index7)
                        {
                            for (int index8 = 0; index8 < num2; ++index8)
                                colors[num1++] = index1 % 2 != 0 ? (index7 % 2 == 0 ? fColor : bColor) : (index7 % 2 == 0 ? bColor : fColor);
                            if (index7 == column - 1)
                            {
                                for (int index9 = 0; index9 < num4; ++index9)
                                    colors[num1++] = index1 % 2 != 0 ? (index7 % 2 == 0 ? fColor : bColor) : (index7 % 2 == 0 ? bColor : fColor);
                            }
                        }
                    }
                }
            }
            return (Image)Image2Bin.Color2Bmp(colors, x, y);
        }
    }
}
