//solution is slow however. might be improvable by changing the starting position etc.

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int* position_ptr = nullptr;
    int* position_ptr_before = nullptr;

    size_t position = 0;
    size_t position1 = 0;
    size_t position2 = 0;

    bool pick1 = true;
    float target = (nums1.size() + nums2.size()) / 2.0 - 0.5;
    if (nums1.size() > 0 && nums2.size() > 0)
    {
        if (nums1[0] > nums2[0])
        {
            position_ptr = &nums2[position2];
            position_ptr_before = position_ptr;
            pick1 = false;
            position2++;
        }
        else
        {
            position_ptr = &nums1[position1];
            position_ptr_before = position_ptr;
            position1++;
        }
    }
    else {
        if (nums1.size() > 0)
        {
            position_ptr = &nums1[position1];
            position_ptr_before = position_ptr;
            position1++;
        }
        else {
            position_ptr = &nums2[position2];
            position_ptr_before = position_ptr;
            pick1 = false;
            position2++;
        }
    }

    while (true)
    {
        if (position >= target)
        {
            break;
        }
        position++;

        if (position1 >= nums1.size())
        {
            //st::cout << "inconly2" << std::endl;
            position_ptr_before = position_ptr;
            position_ptr = &nums2[position2];
            position2++;
            pick1 = false;
            continue;
        }
        if (position2 >= nums2.size())
        {
            //st::cout << "inconly1" << std::endl;
            position_ptr_before = position_ptr;
            position_ptr = &nums1[position1];
            position1++;
            pick1 = true;
            continue;
        }

        if (nums1[position1] > nums2[position2])
        {
            //st::cout << "inc2" << std::endl;
            position_ptr_before = position_ptr;
            position_ptr = &nums2[position2];
            position2++;
            pick1 = false;
            continue;
        }
        else {
            //st::cout << "inc1" << std::endl;
            position_ptr_before = position_ptr;
            position_ptr = &nums1[position1];
            position1++;
            pick1 = true;
            continue;
        }
    }

    //st::cout << target << std::endl;
    //st::cout << position << std::endl;
    //st::cout << position1 << std::endl;
    //st::cout << position2 << std::endl;

    if ((nums1.size() + nums2.size()) % 2 == 0) //even
    {
        //st::cout << "even" << std::endl;
        return (*position_ptr + *position_ptr_before) / 2.0;
    }
    else
    {
        //st::cout << "odd" << std::endl;
        return *position_ptr;
    }
}
};