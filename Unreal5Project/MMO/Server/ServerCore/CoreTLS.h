#pragma once
#include <stack>

/*
thread_local�� C++11���� ���Ե� �����庰(thread-local) ���� ������ ������ ���� ������ ���� Ű�����Դϴ�.
��, �� �����尡 ���������� �ش� ������ ���纻�� ���� �� �ֵ��� �����մϴ�.

�Ϲ����� ���� ������ static ������ ��� �����尡 ����������, thread_local�� ����ϸ� �� �����帶�� �������� ���� �����մϴ�.
�̷��� �ϸ� ��Ƽ������ ȯ�濡���� ����ȭ ���� �����ϰ� ����� �� �ִ� ������ ���� �� �ֽ��ϴ�.
*/

extern thread_local uint32				LThreadId;
extern thread_local uint64				LEndTickCount;

extern thread_local class JobQueue* LCurrentJobQueue;