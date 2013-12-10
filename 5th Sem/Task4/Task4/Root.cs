﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task4
{
    public struct Segment
    {
        public Segment(float _a, float _b)
        {
            a = _a;
            b = _b;
        }
        public float a, b;
    }

    public abstract class SegmentRootMethod
    {
        abstract public float findRoot(Segment ab, Interpolation F, float X, float e);
    }

    public class BisectionMethod : SegmentRootMethod
    {
        override public float findRoot(Segment ab, Interpolation F, float X, float e)
        {
            float a = ab.a;
            float b = ab.b;
            float fa, fb, fc;

            //N = 0;

            while (true)
            {
                fa = F.Calc(a, new LagrangeMethod()) - X;
                fb = F.Calc(b, new LagrangeMethod()) - X;
                fc = F.Calc((a + b) / 2.0f, new LagrangeMethod()) - X;

                if ((b - a) < 2 * e)
                    break;
                if (fc == 0)
                    break;
           //     System.Console.WriteLine("x = {0} {1}", b-a, 2 * e);
              //  N++;

                if (fa * fc < 0)
                    b = (a + b) / 2.0f;
                else
                    a = (a + b) / 2.0f;
            }
            return (a + b) / 2.0f;
        }
    }

    class RootSolution
    {
        public static float MINH = 0.0005f;

        private List<Segment> mSegments;
        private Interpolation mFunc;

        private float mh;
        private float me;
        private float ma;
        private float mb;
        private bool inv;
        private float mX;


        public RootSolution()
        {
            mSegments = new List<Segment>();
        }

        public void Init(float _e, float _h, float _a, float _b, bool _inv)
        {
            me = _e;
            mh = _h;
            ma = _a;
            mb = _b;
            inv = _inv;
            mX = 0;

            mSegments.Clear();
        }

        public Interpolation Func
        {
            get
            {
                return mFunc;
            }
            set
            {
                mFunc = value;
            }

        }

        public float X
        {
            get{return mX;}
            set{mX = value;}
        }

        public void Div()
        {
            float h = mh;
            int lCount = -1;// prev segments count
            int count = 0;//curent count

            float a = ma;
            float b = 0;

            bool calcH = false;

            if (h < 0) // if we need to calculate h automatic
            {
                h = (mb - ma) / 5.0f;
                calcH = true;
            }
            while (true) // for auto calc
            {
                count = 0;
                a = ma;
                mSegments.Clear();

                while (a < mb)
                {
                    b = Math.Min(mb, a + h);
                    if ((mFunc.Calc(a, new LagrangeMethod()) - mX) * (mFunc.Calc(b, new LagrangeMethod()) - mX) < 0)
                    {
                        count++;
                        mSegments.Add(new Segment(a, b));
                    }
                    a = b;
                }

                if (!calcH)
                    break;

                if ((count == lCount) || (h < MINH))
                    break;
                lCount = count;
                h /= 11.3f;
            }

            mh = h;
        }

        public List<float> getRoots(SegmentRootMethod method)
        {
            Div();
            List<float> roots = new List<float>();

            for (int i = 0; i < mSegments.Count; i++)
                roots.Add(method.findRoot(mSegments[i], mFunc, mX, me));
            return roots;
        }
    }
}