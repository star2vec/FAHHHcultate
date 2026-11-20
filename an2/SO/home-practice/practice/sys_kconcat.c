int sys_kconcat(struct proc *p, void *v, register_t *retval) {
    struct sys_kconcat_args *uap = v;
    size_t len = SCARG(uap, len);
    size_t l1, l2;
    
    char *kbuf;
    int error;
    
    if (len==0 || len>4096) {
        return EINVAL;
    }
    
    kbuf = malloc(len, M_TEMP, M_WAITOK);
    
    error = copyinstr(SCARG(uap, s1), kbuf, len, &l1);
    if (error == 0) {
        error = copyinstr(SCARG(uap, s2), kbuf+l1-1, len-l1+1, &l2);
    }
    
    if (error==0) {
        error = copyoutstr(kbuf, SCARG(uap, dst), len, NULL);
    }
    
    free(kbuf, M_TEMP, len);
    if (error != 0) {
        return error;
    }
    
    *retval = l1-1+l2-1;
    return 0;
}
