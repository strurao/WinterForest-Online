#include "Panel.h"

class TestPanel : public Panel
{
	using Super = Panel;
public:
	TestPanel();
	virtual ~TestPanel() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void OnClickStartButton();
	void OnClickEditButton();
	void OnClickExitButton();

	int32 _count = 0;
};
