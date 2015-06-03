using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace KorTextDiv
{
    class Program
    {
            
        static void Main(string[] args)
        {
            string Input = "", Output = "";
            using (StreamReader sr = new StreamReader("data.txt", Encoding.GetEncoding("ks_c_5601-1987")))
            {
                Input += sr.ReadToEnd();
                sr.Close();
            }
            Console.WriteLine("Text input complete.");
            //한글 데이터 입력
            Console.WriteLine("Working... \n");
            Output = Seperate(Input);
            Input = Console.ReadLine();
            //빈도 분석

        }
        //.net에서 string형은 유니코드형식
        //모든데이터가 unicode로 되어있다고 가정하고 시작한다.
        //입력데이터가 유니코드가아닐경우 string.format로 유니코드로 변환해주어야한다.

        private static string Seperate(string data)
        {
            int a, b, c;//자소버퍼 초성중성종성순
            string result = " ";//분리결과가 저장되는 문자열
            int cnt;
            //한글의 유니코드
            //http://nonstop.pe.kr/dotnet/409
            // ㄱ ㄲ ㄴ ㄷ ㄸ ㄹ ㅁ ㅂ ㅃ ㅅ ㅆ ㅇ ㅈ ㅉ ㅊ ㅋ ㅌ ㅍ ㅎ
            int[] ChoSung ={ 0x3131, 0x3132, 0x3134, 0x3137, 0x3138, 0x3139, 0x3141
            , 0x3142, 0x3143, 0x3145, 0x3146, 0x3147, 0x3148, 0x3149, 0x314a
            , 0x314b, 0x314c, 0x314d, 0x314e };

            // ㅏ ㅐ ㅑ ㅒ ㅓ ㅔ ㅕ ㅖ ㅗ ㅘ ㅙ ㅚ ㅛ ㅜ ㅝ ㅞ ㅟ ㅠ ㅡ ㅢ ㅣ
            int[] JwungSung = {   0x314f, 0x3150, 0x3151, 0x3152, 0x3153, 0x3154, 0x3155
            , 0x3156, 0x3157, 0x3158, 0x3159, 0x315a, 0x315b, 0x315c, 0x315d, 0x315e
            , 0x315f, 0x3160, 0x3161, 0x3162, 0x3163 };

            // ㄱ ㄲ ㄳ ㄴ ㄵ ㄶ ㄷ ㄹ ㄺ ㄻ ㄼ ㄽ ㄾ ㄿ ㅀ ㅁ ㅂ ㅄ ㅅ ㅆ ㅇ ㅈ ㅊ ㅋ ㅌ ㅍ ㅎ
            int[] JongSung = { 0, 0x3131, 0x3132, 0x3133, 0x3134, 0x3135, 0x3136
            , 0x3137, 0x3139, 0x313a, 0x313b, 0x313c, 0x313d, 0x313e, 0x313f
            , 0x3140, 0x3141, 0x3142, 0x3144, 0x3145, 0x3146, 0x3147, 0x3148
            , 0x314a, 0x314b, 0x314c, 0x314d, 0x314e };

            int[]   ChoSungAmount = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int[] JwungSungAmount = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int[]  JongSungAmount = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int CA = 0, WA = 0,JA = 0;
            int x;
            int tmp;
            Boolean OP = false;
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            for (cnt = 0; cnt < data.Length; cnt++)
            {
                x = (int)data[cnt];
                if (stopwatch.ElapsedMilliseconds % 1000 == 0 && OP == false)
                {
                    Console.WriteLine(cnt+"/"+data.Length+", "+((long)cnt * 100 / (long)data.Length) + "% Complete, " + stopwatch.ElapsedMilliseconds / 1000 + " seconds elapsed!");
                    OP = true;
                }
                else if (stopwatch.ElapsedMilliseconds % 1000 > 0)
                    OP = false;
                
                //한글일 경우만 분리 시행
                if (x >= 0xAC00 && x <= 0xD7A3)
                {
                    c = x - 0xAC00;
                    a = c / (21 * 28);
                    c = c % (21 * 28);
                    b = c / 28;
                    c = c % 28;
                    tmp = a + b + c;
                    ChoSungAmount[a]++;
                    CA++;
                    JwungSungAmount[b]++;
                    if (c > 0)
                    {
                        JongSungAmount[c - 1]++;
                        JA++;   
                    }
                    //텍스트 로그 출력
                    /*result += string.Format("{0}{1}", (char)ChoSung[a], (char)JwungSung[b]);
                    // $c가 0이면, 즉 받침이 있을경우
                    if (c != 0)
                        result += string.Format("{0}", (char)JongSung[c]);
                    */
                }
                else
                {
                    //한글 아니면 삭제크리
                    //result += string.Format("{0}", (char)x);
                }
            }
            string TextOut ="";
            Console.WriteLine("\nCounting Complete!\n총 글자 수 : " + CA + ", 받침 수 : " + JA);
            Console.WriteLine("ㄱ\tㄲ\tㄴ\tㄷ\tㄸ\tㄹ\tㅁ\tㅂ\tㅃ\tㅅ\tㅆ\tㅇ\tㅈ\tㅉ\tㅊ\tㅋ\tㅌ\tㅍ\tㅎ");
            for (int temp = 0; temp < ChoSungAmount.Length; temp++)
            {
                Console.Write(ChoSungAmount[temp] + "\t");
                TextOut += ChoSungAmount[temp] + "\t";
            }
            Console.WriteLine("\n\nㅏ\tㅐ\tㅑ\tㅒ\tㅓ\tㅔ\tㅕ\tㅖ\tㅗ\tㅘ\tㅙ\tㅚ\tㅛ\tㅜ\tㅝ\tㅞ\tㅟ\tㅠ\tㅡ\tㅢ\tㅣ");
            TextOut += "\t";
            for (int temp = 0; temp < JwungSungAmount.Length; temp++)
            {
                Console.Write(JwungSungAmount[temp] + "\t");
                TextOut += JwungSungAmount[temp] + "\t";
            }
            Console.WriteLine("\n\nㄱ\tㄲ\tㄳ\tㄴ\tㄵ\tㄶ\tㄷ\tㄹ\tㄺ\tㄻ\tㄼ\tㄽ\tㄾ\tㄿ\tㅀ\tㅁ\tㅂ\tㅄ\tㅅ\tㅆ\tㅇ\tㅈ\tㅊ\tㅋ\tㅌ\tㅍ\tㅎ");
            TextOut += "\t";
            for (int temp = 0; temp < JongSungAmount.Length; temp++)
            {
                Console.Write(JongSungAmount[temp] + "\t");
                TextOut += JongSungAmount[temp] + "\t";
            }
            System.IO.File.WriteAllText("Output.txt", TextOut);
            //System.IO.File.WriteAllText("OutputAll.txt", result);

            return TextOut;
        }

    }
}
