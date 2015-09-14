struct skip_node
{
    int         element;
    skip_list   right;
    skip_list   down;
};

static position bottom = NULL;
static position tail    = NULL;

skip_list 
Initialize()
{
    skip_list L ;
    if ( NULL == bottom) {
        bottom = malloc(sizeof(struct skip_node));
        if ( NULL ==bottom ) {
            printf("out of space !\n");
        }
        bottom->right = bottom->down = bottom;
        
        tail = malloc(sizeof(struct skip_node))
        if (NULL == tail) {
             printf("out of space !\n");
        }
        tail->element = Infinity ;
        tail->right = tail ;
        return L ;
    }

}