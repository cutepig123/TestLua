nGlobal = 10 --һ��ȫ�ֵ����α��� 
strGlobal = "hello i am in lua" --һ��ȫ�ֵ��ַ������� 
--һ������ֵΪint���͵ĺ��� 
function add(a, b) 
    return a+b 
end 
--һ������ֵΪstring���͵ĺ��� 
function strEcho(a) 
    print(a) 
    return 'haha i have print your input param' 
end 
cppapi.testFunc() --����c++��¶��һ�����Ժ��� 
t={name='ettan', age=23, desc='��ֵ��������'}
