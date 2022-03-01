#include "httpstatusinfo.h"

shared_ptr<HttpStatusInfo> HttpStatusInfo::m_instance = nullptr;

HttpStatusInfo::HttpStatusInfo(QObject* parent) : QObject(parent)
{
    m_httpStatusInfos[200] = "（成功） 服务器已成功处理了请求。 通常，这表示服务器提供了请求的网页。";
    m_httpStatusInfos[201] = "（已创建） 请求成功并且服务器创建了新的资源。";
    m_httpStatusInfos[202] = "（已接受） 服务器已接受请求，但尚未处理。";
    m_httpStatusInfos[203] = "（非授权信息） 服务器已成功处理了请求，但返回的信息可能来自另一来源。";
    m_httpStatusInfos[204] = "（无内容） 服务器成功处理了请求，但没有返回任何内容。";
    m_httpStatusInfos[205] = "（重置内容） 服务器成功处理了请求，但没有返回任何内容。";
    m_httpStatusInfos[206] = "（部分内容） 服务器成功处理了部分 GET 请求。";
    m_httpStatusInfos[300] = "（多种选择） 针对请求，服务器可执行多种操作。 服务器可根据请求者 (user agent) 选择一项操作，或提供操作列表供请求者选择。";
    m_httpStatusInfos[301] = "（永久移动） 请求的网页已永久移动到新位置。 服务器返回此响应（对 GET 或 HEAD 请求的响应）时，会自动将请求者转到新位置。";
    m_httpStatusInfos[302] = "（临时移动） 服务器目前从不同位置的网页响应请求，但请求者应继续使用原有位置来进行以后的请求。";
    m_httpStatusInfos[303] = "（查看其他位置） 请求者应当对不同的位置使用单独的 GET 请求来检索响应时，服务器返回此代码。";
    m_httpStatusInfos[304] = "（未修改） 自从上次请求后，请求的网页未修改过。 服务器返回此响应时，不会返回网页内容。";
    m_httpStatusInfos[305] = "（使用代理） 请求者只能使用代理访问请求的网页。 如果服务器返回此响应，还表示请求者应使用代理。";
    m_httpStatusInfos[307] = "（临时重定向） 服务器目前从不同位置的网页响应请求，但请求者应继续使用原有位置来进行以后的请求。";
    m_httpStatusInfos[400] = "（错误请求） 服务器不理解请求的语法。";
    m_httpStatusInfos[401] = "（未授权） 请求要求身份验证。 对于需要登录的网页，服务器可能返回此响应。";
    m_httpStatusInfos[403] = "（禁止） 服务器拒绝请求。";
    m_httpStatusInfos[404] = "（未找到） 服务器找不到请求的网页。";
    m_httpStatusInfos[405] = "（方法禁用） 禁用请求中指定的方法。";
    m_httpStatusInfos[406] = "（不接受） 无法使用请求的内容特性响应请求的网页。";
    m_httpStatusInfos[407] = "（需要代理授权） 此状态代码与 401（未授权）类似，但指定请求者应当授权使用代理。";
    m_httpStatusInfos[408] = "（请求超时） 服务器等候请求时发生超时。";
    m_httpStatusInfos[409] = "（冲突） 服务器在完成请求时发生冲突。 服务器必须在响应中包含有关冲突的信息。";
    m_httpStatusInfos[410] = "（已删除） 如果请求的资源已永久删除，服务器就会返回此响应。";
    m_httpStatusInfos[411] = "（需要有效长度） 服务器不接受不含有效内容长度标头字段的请求。";
    m_httpStatusInfos[412] = "（未满足前提条件） 服务器未满足请求者在请求中设置的其中一个前提条件。";
    m_httpStatusInfos[413] = "（请求实体过大） 服务器无法处理请求，因为请求实体过大，超出服务器的处理能力。";
    m_httpStatusInfos[414] = "（请求的 URI 过长） 请求的 URI（通常为网址）过长，服务器无法处理。";
    m_httpStatusInfos[415] = "（不支持的媒体类型） 请求的格式不受请求页面的支持。";
    m_httpStatusInfos[416] = "（请求范围不符合要求） 如果页面无法提供请求的范围，则服务器会返回此状态代码。";

}

HttpStatusInfo::~HttpStatusInfo()
{
    qDebug() << "HttpStatusInfo::~HttpStatusInfo()";

}

QString HttpStatusInfo::getStatusInfo(int code)
{
    return m_httpStatusInfos[code];

}

HttpStatusInfo* httpStatusInfo()
{
    if (HttpStatusInfo::m_instance == nullptr)
    {
        HttpStatusInfo::m_instance = make_shared<HttpStatusInfo>(new HttpStatusInfo());
    }
    return HttpStatusInfo::m_instance.get();
}
