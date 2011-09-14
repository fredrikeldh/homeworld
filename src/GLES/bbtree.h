/*
static void
g_tree_insert_internal (GTree    *tree,
                        gpointer  key,
                        gpointer  value,
                        gboolean  replace)
{
  GTreeNode *node;
  GTreeNode *path[MAX_GTREE_HEIGHT];
  int idx;

  g_return_if_fail (tree != NULL);

  if (!tree->root)
    {
      tree->root = g_tree_node_new (key, value);
      tree->nnodes++;
      return;
    }

  idx = 0;
  path[idx++] = NULL;
  node = tree->root;

  while (1)
    {
      int cmp = tree->key_compare (key, node->key, tree->key_compare_data);

      if (cmp == 0)
        {
          if (tree->value_destroy_func)
            tree->value_destroy_func (node->value);

          node->value = value;

          if (replace)
            {
              if (tree->key_destroy_func)
                tree->key_destroy_func (node->key);

              node->key = key;
            }
          else
            {
              // free the passed key
              if (tree->key_destroy_func)
                tree->key_destroy_func (key);
            }

          return;
        }
      else if (cmp < 0)
        {
          if (node->left_child)
            {
              path[idx++] = node;
              node = node->left;
            }
          else
            {
              GTreeNode *child = g_tree_node_new (key, value);

              child->left = node->left;
              child->right = node;
              node->left = child;
              node->left_child = TRUE;
              node->balance -= 1;

	      tree->nnodes++;

              break;
            }
        }
      else
        {
          if (node->right_child)
            {
              path[idx++] = node;
              node = node->right;
            }
          else
            {
              GTreeNode *child = g_tree_node_new (key, value);

              child->right = node->right;
              child->left = node;
              node->right = child;
              node->right_child = TRUE;
              node->balance += 1;

	      tree->nnodes++;

              break;
            }
        }
    }

  // restore balance. This is the goodness of a non-recursive
  //   implementation, when we are done with balancing we 'break'
  //   the loop and we are done.
  while (1)
    {
      GTreeNode *bparent = path[--idx];
      gboolean left_node = (bparent && node == bparent->left);
      g_assert (!bparent || bparent->left == node || bparent->right == node);

      if (node->balance < -1 || node->balance > 1)
        {
          node = g_tree_node_balance (node);
          if (bparent == NULL)
            tree->root = node;
          else if (left_node)
            bparent->left = node;
          else
            bparent->right = node;
        }

      if (node->balance == 0 || bparent == NULL)
        break;

      if (left_node)
        bparent->balance -= 1;
      else
        bparent->balance += 1;

      node = bparent;
    }
}
*/
template<int... test>
class test
{
	template<int lowest>
	int getLowest()
	{
		return lowest;
	}

	template<int first, int second, int... test>
	int getLowest()
	{
		if( first < second )
			return getLowest<first, test...>();
		else
			return getLowest<second, test...>();
	}
	
	template<int highest>
	int getHighest()
	{
		return highest;
	}
	
	template<int first, int second, int... test>
	int getHighest()
	{
		if( first > second )
			return getHighest<first, test...>();
		else
			return getHighest<second, test...>();
	}

	template<int... test>
	int getMiddle()
	{
		int lowest = getLowest<test...>();
		int highest = getHighest<test...>();
		
		int middle = lowest + ( highest - lowest ) / 2;
		
		return middle;
	}
	
	template<int first, int second, int... test>
	void add()
	{
		insert<first>();
		add<second, test...>();
	}

	template<int... test>
	void init()
	{
		Tree* tree = new Tree();
		add<first, test>();
	}
	
	template<int first>
	void insert()
	{
		int key = first;
		int value = key;
		
		if( !root )
		{
			root = new TreeNode(key, value);
			nnodes++;
			return;
		}

		int idx = 0;
		
		TreeNode *path[MAX_GTREE_HEIGHT];
		path[idx++] = NULL;
		TreeNode& node = *root;
	
		while( true )
		{
			int cmp = key_compare (key, node.key, key_compare_data);

			if( cmp == 0 )
			{
				if( tree->value_destroy_func )
					tree->value_destroy_func (node->value);

				node.value = value;

				if( replace )
				{
					if (tree->key_destroy_func)
						tree->key_destroy_func (node->key);

					node->key = key;
				}
				else
				{
					// free the passed key
					if (tree->key_destroy_func)
						tree->key_destroy_func (key);
				}

				return;
			}
			else if (cmp < 0)
			{
				if( node.left_child )
				{
					path[idx++] = node;
					node = node.left;
				}
				else
				{
					TreeNode *child = new TreeNode(key, value);

					child->left = node.left;
					child->right = node;
					node.left = *child;
					node.left_child = true;
					node.balance -= 1;

					nnodes++;

					break;
				}
			}
			else //(cmp > 0)
			{
				if (node.right_child)
				{
					path[idx++] = &node;
					node = *node.right;
				}
				else
				{
					TreeNode *child = new TreeNode(key, value);

					child->right = node.right;
					child->left = &node;
					node.right = child;
					node.right_child = true;
					node.balance += 1;

					nnodes++;

					break;
				}
			}
		}
		
		// restore balance. This is the goodness of a non-recursive
		// implementation, when we are done with balancing we 'break'
		// the loop and we are done.
		while (1)
		{
			TreeNode *bparent = path[--idx];
			bool left_node = (bparent && node == bparent->left);
			//g_assert (!bparent || bparent->left == node || bparent->right == node);

			if (node.balance < -1 || node.balance > 1)
			{
				node = Balance(node);
				
				if (bparent == NULL)
					root = node;
				else if (left_node)
					bparent->left = &node;
				else
					bparent->right = &node;
			}

			if (node->balance == 0 || bparent == NULL)
				break;

			if (left_node)
				bparent->balance -= 1;
			else
				bparent->balance += 1;

			node = *bparent;
		}
	}
}
