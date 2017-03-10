#ifndef XMS_ALG_SERVER_COMMON_H
#define XMS_ALG_SERVER_COMMON_H

enum AlgType {
    Alg_IPD = 11,
    Alg_VFD = 12,
    Alg_PFR = 13,
};

Q_DECLARE_METATYPE(AlgType); //通过Q_DECLARE_METATYPE声明后，就可以让自定义的类型设置到QVariant

#endif // XMS_ALG_SERVER_COMMON_H
