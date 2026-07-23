# CX900 工具 - 使用说明

## 文件关联功能

### 功能说明
- `.CXKJ` 扩展名文件会自动关联到程序图标
- 双击 `.CXKJ` 文件会直接启动程序并加载该文件

### 实现原理
1. **文件注册表关联**: 程序启动时会在 `HKEY_CURRENT_USER\Software\Classes` 下注册 `.cxkj` 扩展名关联
2. **图标设置**: 使用程序图标 `Construction_(159).ico` 作为 `.CXKJ` 文件的显示图标
3. **命令行参数处理**: 支持通过命令行参数接收文件路径

### 自动注册
程序每次启动时会自动注册文件关联,无需手动操作。

### 手动注册
如需手动注册文件关联,可以运行:
```
CX900.exe --register-association
```

## 响应式布局功能

### 功能说明
- 界面能够自适应不同分辨率的显示器
- 支持窗体大小调整时自动调整控件布局
- 保持 SplitContainer 分割比例

### 关键特性
1. **Tab控件填充**: tabControl1 设置为 `DockStyle.Fill`,自动填充整个容器
2. **页面自动滚动**: 所有 TabPage 设置 `AutoScroll = true`,防止内容被截断
3. **分割器比例调整**: 窗体大小改变时自动调整 SplitContainer 的分割比例
4. **最小窗口限制**: 窗体最小尺寸设置为 1000x500,防止过小导致布局错乱

### 支持的分辨率
- 1920x1080
- 1366x768  
- 1024x768
- 其他标准分辨率

## 新增文件

### FileAssociationManager.cs
文件关联管理类,负责:
- 注册/注销 `.CXKJ` 文件关联
- 处理命令行参数
- 管理程序图标

### ResponsiveLayoutHelper.cs
响应式布局助手类,提供:
- 控件位置自动调整
- 按比例缩放布局
- Anchor/Dock 属性支持

## 使用方法

### 正常启动
直接双击 `CX900.exe` 启动程序。

### 打开项目文件
1. 双击 `.CXKJ` 文件,程序会自动启动并加载
2. 或者在程序中通过菜单"文件 > 打开文件"选择 `.CXKJ` 文件

### 调整窗口大小
拖动窗口边缘或角落,界面会自动调整:
- TabControl 自动填充
- 控件按比例调整位置
- 保持相对布局

## 技术细节

### 文件关联注册表结构
```
HKEY_CURRENT_USER\Software\Classes\
├── .cxkj\ (默认) = "CX900.File"
└── CX900.File\
    ├── (默认) = "CX900 Project File"
    ├── DefaultIcon\ (默认) = "程序路径,0"
    └── shell\open\command\ (默认) = "程序路径" "%1"
```

### 响应式布局关键代码
```csharp
// 窗体大小改变事件
private void MainForm_Resize(object sender, EventArgs e)
{
    if (this.WindowState == FormWindowState.Minimized)
        return;
    
    // 调整分割器比例
    if (splitContainer1 != null)
    {
        int newSplitterDistance = (int)(this.ClientSize.Width * _initialSplitterDistanceRatio);
        splitContainer1.SplitterDistance = newSplitterDistance;
    }
}
```

## 注意事项

1. **图标文件**: 确保 `Construction_(159).ico` 文件存在于程序目录
2. **管理员权限**: 文件关联注册在当前用户级别,无需管理员权限
3. **系统图标缓存**: 注册后会自动刷新系统图标缓存
4. **文件路径**: 支持包含空格和中文的文件路径

## 故障排除

### 文件不显示图标
- 等待几秒钟让系统图标缓存刷新
- 手动重启资源管理器

### 双击文件无反应
- 检查文件路径是否正确
- 查看是否有错误提示信息
- 确认程序没有被防火墙阻止

### 窗口布局错乱
- 恢复窗口到默认大小
- 检查最小窗口尺寸限制(1000x500)

## 更新日志

### v1.1.0
- 新增 `.CXKJ` 文件关联功能
- 新增响应式布局支持
- 新增命令行参数处理
- 优化界面在不同分辨率下的显示效果
