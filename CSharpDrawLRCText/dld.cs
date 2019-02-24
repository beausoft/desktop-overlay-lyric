using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices; // 用 DllImport 需用此 命名空间
using System.Reflection; // 使用 Assembly 类需用此 命名空间
using System.Reflection.Emit; // 使用 ILGenerator 需用此 命名空间

namespace CSharpDrawLRCText
{
    /// <summary>
    /// 参数传递方式枚举 ,ByValue 表示值传递 ,ByRef 表示址传递
    /// </summary>
    public enum ModePass
    {
        ByValue = 0x0001,
        ByRef = 0x0002
    }
    public class dld
    {
        /// <summary>
        /// 原型是 :HMODULELoadLibrary(LPCTSTR lpFileName);
        /// </summary>
        /// <param name="lpFileName">DLL 文件名 </param>
        /// <returns> 函数库模块的句柄 </returns>
        [DllImport("kernel32.dll")]
        static extern IntPtr LoadLibrary(string lpFileName);
        /// <summary>
        /// 原型是 : FARPROCGetProcAddress(HMODULE hModule, LPCWSTR lpProcName);
        /// </summary>
        /// <param name="hModule"> 包含需调用函数的函数库模块的句柄 </param>
        /// <param name="lpProcName"> 调用函数的名称 </param>
        /// <returns> 函数指针 </returns>
        [DllImport("kernel32.dll")]
        static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);
        /// <summary>
        /// 原型是 : BOOLFreeLibrary(HMODULE hModule);
        /// </summary>
        /// <param name="hModule"> 需释放的函数库模块的句柄 </param>
        /// <returns> 是否已释放指定的 Dll</returns>
        [DllImport("kernel32",EntryPoint="FreeLibrary",SetLastError=true)]
        static extern bool FreeLibrary(IntPtr hModule);
        /// <summary>
        /// Loadlibrary 返回的函数库模块的句柄
        /// </summary>
        private IntPtr hModule=IntPtr.Zero;
        /// <summary>
        /// GetProcAddress 返回的函数指针
        /// </summary>
        private IntPtr farProc=IntPtr.Zero;

        /// <summary>
        /// 装载 Dll
        /// </summary>
        /// <param name="lpFileName">DLL 文件名 </param>
        public void LoadDll(string lpFileName)
        {
            hModule = LoadLibrary(lpFileName);
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 没有找到 :" + lpFileName + "."));
        }
        /// <summary>
        /// 若已有已装载Dll的句柄，可以使用LoadDll方法的第二个版本：
        /// </summary>
        /// <param name="HMODULE">DLL句柄</param>
        public void LoadDll(IntPtr HMODULE)
        {
            if(HMODULE==IntPtr.Zero)
            throw(new Exception(" 所传入的函数库模块的句柄 HMODULE 为空 ." ));
            hModule=HMODULE;
        }
        /// <summary>
        /// 获得函数指针
        /// </summary>
        /// <param name="lpProcName">调用函数的名称</param>
        public void LoadFun(string lpProcName)
        { // 若函数库模块的句柄为空，则抛出异常
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 函数库模块的句柄为空 , 请确保已进行 LoadDll 操作 !"));
            // 取得函数指针
            farProc = GetProcAddress(hModule, lpProcName);
            // 若函数指针，则抛出异常
            if (farProc == IntPtr.Zero)
                throw (new Exception(" 没有找到 :" + lpProcName + " 这个函数的入口点 "));
        }

        /// <summary>
        /// 获得函数指针
        /// </summary>
        /// <param name="lpFileName"> 包含需调用函数的 DLL 文件名 </param>
        /// <param name="lpProcName"> 调用函数的名称 </param>
        public void LoadFun(string lpFileName, string lpProcName)
        { // 取得函数库模块的句柄
            hModule = LoadLibrary(lpFileName);
            // 若函数库模块的句柄为空，则抛出异常
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 没有找到 :" + lpFileName + "."));
            // 取得函数指针
            farProc = GetProcAddress(hModule, lpProcName);
            // 若函数指针，则抛出异常
            if (farProc == IntPtr.Zero)
                throw (new Exception(" 没有找到 :" + lpProcName + " 这个函数的入口点 "));
        }

        /// <summary>
        /// 卸载 Dll
        /// </summary>
        public void UnLoadDll()
        {
            FreeLibrary(hModule);
            hModule = IntPtr.Zero;
            farProc = IntPtr.Zero;
        }
        /// <summary>
        /// 调用所设定的函数
        /// </summary>
        /// <param name="ObjArray_Parameter">实参</param>
        /// <param name="TypeArray_ParameterType">实参类型</param>
        /// <param name="ModePassArray_Parameter">实参传送方式</param>
        /// <param name="Type_Return">返回类型</param>
        /// <returns>返回所调用函数的object</returns>
        public object Invoke(object[] ObjArray_Parameter, Type[] TypeArray_ParameterType, ModePass[] ModePassArray_Parameter, Type Type_Return) {
            //下面 3 个 if 是进行安全检查 , 若不能通过 , 则抛出异常 
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 函数库模块的句柄为空 , 请确保已进行 LoadDll 操作 !"));
            if (farProc == IntPtr.Zero)
                throw (new Exception(" 函数指针为空 , 请确保已进行 LoadFun 操作 !"));
            if (ObjArray_Parameter.Length != ModePassArray_Parameter.Length)
                throw (new Exception(" 参数个数及其传递方式的个数不匹配 .")); 
            //下面是创建 MyAssemblyName 对象并设置其 Name 属性
            AssemblyName MyAssemblyName = new AssemblyName();
            MyAssemblyName.Name = "InvokeFun";
            //生成单模块配件
            AssemblyBuilder MyAssemblyBuilder = AppDomain.CurrentDomain.DefineDynamicAssembly(MyAssemblyName, AssemblyBuilderAccess.Run);
            ModuleBuilder MyModuleBuilder = MyAssemblyBuilder.DefineDynamicModule("InvokeDll");
            //定义要调用的方法 , 方法名为“ MyFun ”，返回类型是“ Type_Return ”参数类型是“ TypeArray_ParameterType ”
            MethodBuilder MyMethodBuilder = MyModuleBuilder.DefineGlobalMethod("MyFun", MethodAttributes.Public | MethodAttributes.Static, Type_Return, TypeArray_ParameterType);
            //获取一个 ILGenerator ，用于发送所需的 IL 
            ILGenerator IL = MyMethodBuilder.GetILGenerator();
            int i;
            for (i = 0; i < ObjArray_Parameter.Length; i++)
            {
                // 用循环将参数依次压入堆栈
                switch (ModePassArray_Parameter[i])
                {
                    case ModePass.ByValue:
                        IL.Emit(OpCodes.Ldarg, i);
                        break;
                    case ModePass.ByRef:
                        IL.Emit(OpCodes.Ldarga, i);
                        break;
                    default:
                        throw (new Exception(" 第 " + (i + 1).ToString() + " 个参数没有给定正确的传递方式 ."));
                }
            }
            if (IntPtr.Size == 4)
            {// 判断处理器类型 
                IL.Emit(OpCodes.Ldc_I4, farProc.ToInt32());
            }
            else if (IntPtr.Size == 8)
            {
                IL.Emit(OpCodes.Ldc_I8, farProc.ToInt64());
            }
            else
            {
                throw new PlatformNotSupportedException();
            }
            IL.EmitCalli(OpCodes.Calli, CallingConvention.StdCall, Type_Return, TypeArray_ParameterType);
            IL.Emit(OpCodes.Ret); // 返回值
            MyModuleBuilder.CreateGlobalFunctions();
            // 取得方法信息
            MethodInfo MyMethodInfo = MyModuleBuilder.GetMethod("MyFun");
            return MyMethodInfo.Invoke(null, ObjArray_Parameter);// 调用方法，并返回其值
        }
        /// <summary>
        /// 调用所设定的函数
        /// </summary>
        /// <param name="IntPtr_Function">函数指针</param>
        /// <param name="ObjArray_Parameter">实参</param>
        /// <param name="TypeArray_ParameterType">实参类型</param>
        /// <param name="ModePassArray_Parameter">实参传送方式</param>
        /// <param name="Type_Return">返回类型</param>
        /// <returns>返回所调用函数的object</returns>
        public object Invoke(IntPtr IntPtr_Function, object[] ObjArray_Parameter, Type[] TypeArray_ParameterType, ModePass[] ModePassArray_Parameter, Type Type_Return)
        {
            //下面 2 个 if 是进行安全检查 , 若不能通过 , 则抛出异常
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 函数库模块的句柄为空 , 请确保已进行 LoadDll 操作 !"));
            if (IntPtr_Function == IntPtr.Zero)
                throw (new Exception(" 函数指针 IntPtr_Function 为空 !"));
            farProc = IntPtr_Function;
            return Invoke(ObjArray_Parameter, TypeArray_ParameterType, ModePassArray_Parameter, Type_Return);
        }
    }
}
