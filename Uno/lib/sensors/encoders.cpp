#include "encoders.h"

namespace encoders
{
    volatile int encoderCounts[6] = {0, 0, 0, 0, 0, 0};

    namespace
    {
        volatile int lastEncoderState[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        const int encoderPinIndex[12] = {
            FRNT_LEFT_ENCA, FRNT_LEFT_ENCB,
            CNTR_LEFT_ENCA, CNTR_LEFT_ENCB,
            REAR_LEFT_ENCA, REAR_LEFT_ENCB,
            FRNT_RIGHT_ENCA, FRNT_RIGHT_ENCB,
            CNTR_RIGHT_ENCA, CNTR_RIGHT_ENCB,
            REAR_RIGHT_ENCA, REAR_RIGHT_ENCB};

        void encoderISR_FLA();
        void encoderISR_FLB();
        void encoderISR_CLA();
        void encoderISR_CLB();
        void encoderISR_RLA();
        void encoderISR_RLB();
        void encoderISR_FRA();
        void encoderISR_FRB();
        void encoderISR_CRA();
        void encoderISR_CRB();
        void encoderISR_RRA();
        void encoderISR_RRB();

        boolean turningClockwise(int pinAIndex, int pinBIndex)
        {
            boolean lastStateA = lastEncoderState[pinAIndex];
            boolean lastStateB = lastEncoderState[pinBIndex];
            int currentStateA = digitalRead(encoderPinIndex[pinAIndex]);
            int currentStateB = digitalRead(encoderPinIndex[pinBIndex]);

            if (lastStateA == LOW && lastStateB == LOW)
            {
                if (currentStateA == HIGH && currentStateB == LOW)
                    return true;
                if (currentStateA == LOW && currentStateB == HIGH)
                    return false;
            }
            else if (lastStateA == HIGH && lastStateB == LOW)
            {
                if (currentStateA == HIGH && currentStateB == HIGH)
                    return true;
                if (currentStateA == LOW && currentStateB == LOW)
                    return false;
            }
            else if (lastStateA == HIGH && lastStateB == HIGH)
            {
                if (currentStateA == LOW && currentStateB == HIGH)
                    return true;
                if (currentStateA == HIGH && currentStateB == LOW)
                    return false;
            }
            else if (lastStateA == LOW && lastStateB == HIGH)
            {
                if (currentStateA == LOW && currentStateB == LOW)
                    return true;
                if (currentStateA == HIGH && currentStateB == HIGH)
                    return false;
            }

            return false;
        }

        void m_updateCounts(int pinAIndex, int pinBindex, int countIndex)
        {
            if (turningClockwise(pinAIndex, pinBindex))
            {
                encoderCounts[countIndex]++;
            }
            else
            {
                encoderCounts[countIndex]--;
            }
        }

        void encoderISR_FLA()
        {
            m_updateCounts(0, 1, 0);
            lastEncoderState[0] = !lastEncoderState[0];
        }

        void encoderISR_FLB()
        {
            m_updateCounts(1, 0, 0);
            lastEncoderState[1] = !lastEncoderState[1];
        }

        void encoderISR_CLA()
        {
            m_updateCounts(2, 3, 1);
            lastEncoderState[2] = !lastEncoderState[2];
        }

        void encoderISR_CLB()
        {
            m_updateCounts(3, 2, 1);
            lastEncoderState[3] = !lastEncoderState[3];
        }

        void encoderISR_RLA()
        {
            m_updateCounts(4, 5, 2);
            lastEncoderState[4] = !lastEncoderState[4];
        }

        void encoderISR_RLB()
        {
            m_updateCounts(5, 4, 2);
            lastEncoderState[5] = !lastEncoderState[5];
        }

        void encoderISR_FRA()
        {
            m_updateCounts(6, 7, 3);
            lastEncoderState[6] = !lastEncoderState[6];
        }

        void encoderISR_FRB()
        {
            m_updateCounts(7, 6, 3);
            lastEncoderState[7] = !lastEncoderState[7];
        }

        void encoderISR_CRA()
        {
            m_updateCounts(8, 9, 4);
            lastEncoderState[8] = !lastEncoderState[8];
        }

        void encoderISR_CRB()
        {
            m_updateCounts(9, 8, 4);
            lastEncoderState[9] = !lastEncoderState[9];
        }

        void encoderISR_RRA()
        {
            m_updateCounts(10, 11, 5);
            lastEncoderState[10] = !lastEncoderState[10];
        }

        void encoderISR_RRB()
        {
            m_updateCounts(11, 10, 5);
            lastEncoderState[11] = !lastEncoderState[11];
        }
    } // End of anonymous namespace

    void initEncoders()
    {
        attachInterrupt(digitalPinToInterrupt(FRNT_LEFT_ENCA), encoderISR_FLA, CHANGE);
        attachInterrupt(digitalPinToInterrupt(FRNT_LEFT_ENCB), encoderISR_FLB, CHANGE);
        attachInterrupt(digitalPinToInterrupt(CNTR_LEFT_ENCA), encoderISR_CLA, CHANGE);
        attachInterrupt(digitalPinToInterrupt(CNTR_LEFT_ENCB), encoderISR_CLB, CHANGE);
        attachInterrupt(digitalPinToInterrupt(REAR_LEFT_ENCA), encoderISR_RLA, CHANGE);
        attachInterrupt(digitalPinToInterrupt(REAR_LEFT_ENCB), encoderISR_RLB, CHANGE);
        attachInterrupt(digitalPinToInterrupt(FRNT_RIGHT_ENCA), encoderISR_FRA, CHANGE);
        attachInterrupt(digitalPinToInterrupt(FRNT_RIGHT_ENCB), encoderISR_FRB, CHANGE);
        attachInterrupt(digitalPinToInterrupt(CNTR_RIGHT_ENCA), encoderISR_CRA, CHANGE);
        attachInterrupt(digitalPinToInterrupt(CNTR_RIGHT_ENCB), encoderISR_CRB, CHANGE);
        attachInterrupt(digitalPinToInterrupt(REAR_RIGHT_ENCA), encoderISR_RRA, CHANGE);
        attachInterrupt(digitalPinToInterrupt(REAR_RIGHT_ENCB), encoderISR_RRB, CHANGE);
    }
}