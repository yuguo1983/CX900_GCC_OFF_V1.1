using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace CX900
{
    /// <summary>
    /// 响应式布局助手类 - 用于处理不同分辨率下的界面自适应
    /// </summary>
    public class ResponsiveLayoutHelper
    {
        private Form _parentForm;
        private float _initialFormWidth;
        private float _initialFormHeight;
        private Dictionary<Control, Rectangle> _controlOriginalPositions = new Dictionary<Control, Rectangle>();
        private Dictionary<Control, Size> _controlOriginalSizes = new Dictionary<Control, Size>();

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="parentForm">父窗体</param>
        public ResponsiveLayoutHelper(Form parentForm)
        {
            _parentForm = parentForm;
            _initialFormWidth = parentForm.ClientSize.Width;
            _initialFormHeight = parentForm.ClientSize.Height;
        }

        /// <summary>
        /// 记录控件的初始位置和大小
        /// </summary>
        /// <param name="controls">需要记录的控件集合</param>
        public void RecordInitialLayout(IEnumerable<Control> controls)
        {
            foreach (var control in controls)
            {
                if (control != null && !_controlOriginalPositions.ContainsKey(control))
                {
                    _controlOriginalPositions[control] = new Rectangle(
                        control.Location.X,
                        control.Location.Y,
                        control.Size.Width,
                        control.Size.Height
                    );
                    _controlOriginalSizes[control] = control.Size;
                }
            }
        }

        /// <summary>
        /// 根据窗体大小变化调整控件位置和大小
        /// </summary>
        /// <param name="e">Resize事件参数</param>
        public void AdjustLayout(EventArgs e)
        {
            if (_parentForm.WindowState == FormWindowState.Minimized)
                return;

            try
            {
                float widthScale = _parentForm.ClientSize.Width / _initialFormWidth;
                float heightScale = _parentForm.ClientSize.Height / _initialFormHeight;

                foreach (var kvp in _controlOriginalPositions)
                {
                    Control control = kvp.Key;
                    Rectangle originalRect = kvp.Value;

                    if (control != null && !control.IsDisposed)
                    {
                        // 根据控件的Dock和Anchor属性调整
                        switch (control.Dock)
                        {
                            case DockStyle.Fill:
                                // Fill类型的控件自动填充,无需调整
                                break;
                            case DockStyle.Top:
                                control.Height = (int)(originalRect.Height * heightScale);
                                break;
                            case DockStyle.Bottom:
                                control.Height = (int)(originalRect.Height * heightScale);
                                break;
                            case DockStyle.Left:
                                control.Width = (int)(originalRect.Width * widthScale);
                                break;
                            case DockStyle.Right:
                                control.Width = (int)(originalRect.Width * widthScale);
                                break;
                            case DockStyle.None:
                                // 没有Dock设置的控件,根据Anchor调整
                                AdjustControlByAnchor(control, originalRect, widthScale, heightScale);
                                break;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                // 静默处理异常,避免影响程序运行
                System.Diagnostics.Debug.WriteLine($"响应式布局调整失败: {ex.Message}");
            }
        }

        /// <summary>
        /// 根据Anchor属性调整控件
        /// </summary>
        private void AdjustControlByAnchor(Control control, Rectangle originalRect, float widthScale, float heightScale)
        {
            AnchorStyles anchor = control.Anchor;

            // 如果没有设置Anchor,默认为Top|Left
            if (anchor == (AnchorStyles.Top | AnchorStyles.Left))
            {
                // Top|Left: 不需要调整位置和大小
                return;
            }

            // 根据Anchor设置调整位置和大小
            int newX = originalRect.X;
            int newY = originalRect.Y;
            int newWidth = originalRect.Width;
            int newHeight = originalRect.Height;

            if ((anchor & AnchorStyles.Right) != 0 && (anchor & AnchorStyles.Left) != 0)
            {
                // 左右都锚定: 调整宽度
                newWidth = (int)(originalRect.Width * widthScale);
            }

            if ((anchor & AnchorStyles.Bottom) != 0 && (anchor & AnchorStyles.Top) != 0)
            {
                // 上下都锚定: 调整高度
                newHeight = (int)(originalRect.Height * heightScale);
            }

            if ((anchor & AnchorStyles.Right) != 0 && (anchor & AnchorStyles.Left) == 0)
            {
                // 只锚定右侧: 调整X位置
                newX = _parentForm.ClientSize.Width - (int)((_initialFormWidth - originalRect.X - originalRect.Width) * widthScale) - newWidth;
            }

            if ((anchor & AnchorStyles.Bottom) != 0 && (anchor & AnchorStyles.Top) == 0)
            {
                // 只锚定底部: 调整Y位置
                newY = _parentForm.ClientSize.Height - (int)((_initialFormHeight - originalRect.Y - originalRect.Height) * heightScale) - newHeight;
            }

            control.Location = new Point(newX, newY);
            control.Size = new Size(newWidth, newHeight);
        }

        /// <summary>
        /// 更新初始窗体大小(当窗体尺寸发生重大变化时调用)
        /// </summary>
        public void UpdateInitialSize()
        {
            _initialFormWidth = _parentForm.ClientSize.Width;
            _initialFormHeight = _parentForm.ClientSize.Height;
        }
    }

    /// <summary>
    /// TabControl响应式布局扩展方法
    /// </summary>
    public static class TabControlResponsiveHelper
    {
        /// <summary>
        /// 设置TabControl为响应式布局
        /// </summary>
        /// <param name="tabControl">TabControl控件</param>
        public static void SetResponsive(this TabControl tabControl)
        {
            if (tabControl == null) return;

            // 设置为Fill填充整个父容器
            tabControl.Dock = DockStyle.Fill;

            // 为所有TabPage启用自动滚动
            foreach (TabPage tabPage in tabControl.TabPages)
            {
                tabPage.AutoScroll = true;
            }
        }
    }
}
