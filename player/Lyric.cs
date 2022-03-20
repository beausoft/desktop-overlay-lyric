using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace player
{
    public class Lyric
    {

        private IntPtr hHandle = IntPtr.Zero;

        public Lyric()
        {
            hHandle = LyricNative.Create();
        }

        public void Close()
        {
            if(hHandle != IntPtr.Zero)
            {
                LyricNative.Free(hHandle);
                hHandle = IntPtr.Zero;
            }
        }

        public void SetText(string text)
        {
            if (hHandle != IntPtr.Zero) {
                LyricNative.SetText(hHandle, text);
            }
        }

        public void SetScale(float scale)
        {
            if (hHandle != IntPtr.Zero)
            {
                LyricNative.SetScale(hHandle, scale);
            }
        }

        public void Show()
        {
            if (hHandle != IntPtr.Zero)
            {
                LyricNative.Show(hHandle);
            }
        }

        public void Hide()
        {
            if (hHandle != IntPtr.Zero)
            {
                LyricNative.Hide(hHandle);
            }
        }

        public void Update()
        {
            if (hHandle != IntPtr.Zero)
            {
                LyricNative.Update(hHandle);
            }
        }

        public void SetColorStyle(int style)
        {
            if (hHandle != IntPtr.Zero)
            {
                LyricNative.SetColorStyle(hHandle, style);
            }
        }

        public void SetLock(bool status)
        {
            if (hHandle != IntPtr.Zero)
            {
                LyricNative.SetLock(hHandle, status);
            }
        }

        public void SetFont(string name, float size)
        {
            if (hHandle != IntPtr.Zero)
            {
                LyricNative.SetFont(hHandle, name, size);
            }
        }

    }
}
