#ifndef __BASE_STATE_H__
#define __BASE_STATE_H__

class BaseState {
public:
	BaseState() {}
	virtual ~BaseState() {}

	virtual void Update(float tic) = 0;
	virtual void Render() = 0;
};

#endif

// EOF
