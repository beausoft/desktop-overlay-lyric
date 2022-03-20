using System;
using System.Runtime.InteropServices;

namespace player
{
    public static class LyricNative
    {
        [DllImport("lyric.dll", EntryPoint = "CreateLyric", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Create();

        [DllImport("lyric.dll", EntryPoint = "FreeLyric", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Free(IntPtr hHandle);

        [DllImport("lyric.dll", EntryPoint = "SetLyricTextA", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetText(IntPtr hHandle, [MarshalAs(UnmanagedType.LPStr)] string text);

        [DllImport("lyric.dll", EntryPoint = "SetLyricScale", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetScale(IntPtr hHandle, float scale);

        [DllImport("lyric.dll", EntryPoint = "LyricShow", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Show(IntPtr hHandle);

        [DllImport("lyric.dll", EntryPoint = "LyricHide", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Hide(IntPtr hHandle);

        [DllImport("lyric.dll", EntryPoint = "LyricUpdate", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Update(IntPtr hHandle);

        [DllImport("lyric.dll", EntryPoint = "SetLyricColorStyle", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetColorStyle(IntPtr hHandle, int style);

        [DllImport("lyric.dll", EntryPoint = "SetLyricLock", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetLock(IntPtr hHandle, bool status);

        [DllImport("lyric.dll", EntryPoint = "SetLyricFontA", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetFont(IntPtr hHandle, [MarshalAs(UnmanagedType.LPStr)]string fontName, float fontSize);

    }
}
